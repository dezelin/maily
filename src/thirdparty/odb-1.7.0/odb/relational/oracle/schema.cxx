// file      : odb/relational/oracle/schema.cxx
// author    : Constantin Michael <constantin@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v3; see accompanying LICENSE file

#include <set>

#include <odb/relational/schema.hxx>

#include <odb/relational/oracle/common.hxx>
#include <odb/relational/oracle/context.hxx>

using namespace std;

namespace relational
{
  namespace oracle
  {
    namespace schema
    {
      namespace relational = relational::schema;

      struct schema_emitter: relational::schema_emitter
      {
        schema_emitter (const base& x): base (x) {}

        virtual void
        line (const std::string& l)
        {
          // SQLPlus doesn't like empty line in the middle of a statement.
          //
          if (!l.empty ())
          {
            base::line (l);
            last_ = l;
          }
        }

        virtual void
        post ()
        {
          if (!first_) // Ignore empty statements.
          {
            if (last_ == "END;")
              os << endl
                 << '/' << endl
                 << endl;

            else
              os << ';' << endl
                 << endl;
          }
        }

      private:
        string last_;
      };
      entry<schema_emitter> schema_emitter_;

      //
      // File.
      //

      struct schema_file: relational::schema_file, context
      {
        schema_file (const base& x): base (x) {}

        virtual void
        prologue ()
        {
          // Quiet down SQLPlus and make sure it exits with an error
          // code if there is an error.
          //
          os << "SET FEEDBACK OFF;" << endl
             << "WHENEVER SQLERROR EXIT FAILURE;" << endl
             << "WHENEVER OSERROR EXIT FAILURE;" << endl
             << endl;
        }

        virtual void
        epilogue ()
        {
          os << "EXIT;" << endl;
        }
      };
      entry<schema_file> schema_file_;

      //
      // Drop.
      //

      struct drop_table: relational::drop_table, context
      {
        drop_table (base const& x): base (x) {}

        virtual void
        drop (string const& table)
        {
          // Oracle has no IF EXISTS conditional for dropping objects. The
          // PL/SQL approach below seems to be the least error-prone and the
          // most widely used of the alternatives.
          //
          os << "BEGIN" << endl
             << "  BEGIN" << endl
             << "    EXECUTE IMMEDIATE 'DROP TABLE " << quote_id (table) <<
            " CASCADE CONSTRAINTS';" << endl
             << "  EXCEPTION" << endl
             << "    WHEN OTHERS THEN" << endl
             << "      IF SQLCODE != -942 THEN RAISE; END IF;" << endl
             << "  END;"
             << "  BEGIN" << endl
             << "    EXECUTE IMMEDIATE 'DROP SEQUENCE " <<
            quote_id (table + "_seq") << "';" << endl
             << "  EXCEPTION" << endl
             << "    WHEN OTHERS THEN" << endl
             << "      IF SQLCODE != -2289 THEN RAISE; END IF;" << endl
             << "  END;" << endl
             << "  BEGIN" << endl
             << "    EXECUTE IMMEDIATE 'DROP TRIGGER " <<
            quote_id (table + "_trg") << "';" << endl
             << "  EXCEPTION" << endl
             << "    WHEN OTHERS THEN" << endl
             << "      IF SQLCODE != -4080 THEN RAISE; END IF;" << endl
             << "  END;" << endl
             << "END;" << endl;
        }
      };
      entry<drop_table> drop_table_;

      //
      // Create.
      //

      struct create_foreign_key;

      struct create_table: relational::create_table, context
      {
        create_table (base const& x): base (x) {}

        void
        traverse (sema_rel::table&);

      private:
        friend class create_foreign_key;
        set<string> tables_; // Set of tables we have already defined.
      };
      entry<create_table> create_table_;

      struct create_column: relational::create_column, context
      {
        create_column (base const& x): base (x) {}

        virtual void
        null (sema_rel::column& c)
        {
          // Oracle interprets empty VARCHAR2 and NVARCHAR2 strings as
          // NULL. As an empty string is always valid within the C++
          // context, VARCHAR2 and NVARCHAR2 columns are always
          // specified as nullable.
          //
          if (!c.null ())
          {
            // This should never fail since we have already parsed this.
            //
            sql_type const& t (parse_sql_type (c.type ()));

            if (t.type == sql_type::VARCHAR2 || t.type == sql_type::NVARCHAR2)
              return;
          }

          base::null (c);
        }
      };
      entry<create_column> create_column_;

      struct create_foreign_key: relational::create_foreign_key, context
      {
        create_foreign_key (schema_format f, relational::create_table& ct)
            : base (f, ct)
        {
        }

        create_foreign_key (base const& x): base (x) {}

        virtual void
        traverse (sema_rel::foreign_key& fk)
        {
          // If the referenced table has already been defined, do the
          // foreign key definition in the table definition. Otherwise
          // postpone it until pass 2 where we do it via ALTER TABLE
          // (see add_foreign_key below).
          //
          create_table& ct (static_cast<create_table&> (create_table_));

          if (ct.tables_.find (fk.referenced_table ()) != ct.tables_.end ())
          {
            base::traverse (fk);
            fk.set ("oracle-fk-defined", true); // Mark it as defined.
          }
        }

        virtual string
        name (sema_rel::foreign_key& fk)
        {
          // In Oracle, foreign key names are schema-global. Make them
          // unique by prefixing the key name with table name.
          //
          return static_cast<sema_rel::table&> (fk.scope ()).name () +
            '_' + fk.name ();
        }
      };
      entry<create_foreign_key> create_foreign_key_;

      struct add_foreign_key: create_foreign_key, relational::common
      {
        add_foreign_key (schema_format f, relational::create_table& ct)
            : create_foreign_key (f, ct), common (ct.emitter (), ct.stream ())
        {
        }

        virtual void
        traverse (sema_rel::foreign_key& fk)
        {
          if (!fk.count ("oracle-fk-defined"))
          {
            sema_rel::table& t (dynamic_cast<sema_rel::table&> (fk.scope ()));

            pre_statement ();

            os << "ALTER TABLE " << quote_id (t.name ()) << " ADD" << endl;
            base::create (fk);
            os << endl;

            post_statement ();
          }
        }
      };

      void create_table::
      traverse (sema_rel::table& t)
      {
        if (pass_ == 1)
        {
          tables_.insert (t.name ()); // Add it before to cover self-refs.
          base::traverse (t);

          // Create the sequence and trigger if we have auto primary key.
          //
          using sema_rel::primary_key;

          sema_rel::table::names_iterator i (t.find ("")); // Special name.

          primary_key* pk (i != t.names_end ()
                           ? &dynamic_cast<primary_key&> (i->nameable ())
                           : 0);

          if (pk != 0 && pk->auto_ ())
          {
            string const& tname (t.name ());
            string const& cname (pk->contains_begin ()->column ().name ());

            string seq_name (tname + "_seq");
            string trg_name (tname + "_trg");

            // Sequence.
            //
            pre_statement ();

            os_ << "CREATE SEQUENCE " << quote_id (seq_name) << endl
                << "  START WITH 1 INCREMENT BY 1" << endl;

            post_statement ();

            // Trigger.
            //
            pre_statement ();

            os_ << "CREATE TRIGGER " << quote_id (trg_name) << endl
                << "  BEFORE INSERT ON " << quote_id (tname) << endl
                << "  FOR EACH ROW" << endl
                << "BEGIN" << endl
                << "  SELECT " << quote_id (seq_name) << ".nextval " <<
              "INTO :new." << quote_id (cname) << " FROM DUAL;" << endl
                << "END;" << endl;

            post_statement ();
          }

          return;
        }

        // Add foreign keys.
        //
        instance<add_foreign_key> fk (format_, *this);
        trav_rel::names n (*fk);
        names (t, n);
      }
    }
  }
}
