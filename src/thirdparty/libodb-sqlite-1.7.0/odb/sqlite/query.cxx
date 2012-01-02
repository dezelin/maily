// file      : odb/sqlite/query.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#include <cstddef> // std::size_t
#include <cstring> // std::memset

#include <odb/sqlite/query.hxx>

using namespace std;

namespace odb
{
  namespace sqlite
  {
    // query_param
    //

    query_param::
    ~query_param ()
    {
    }

    // query_params
    //

    query_params::
    query_params (const query_params& x)
        : details::shared_base (x),
          params_ (x.params_), bind_ (x.bind_), binding_ (0, 0)
    {
      // Here and below we want to maintain up to date binding info so
      // that the call to binding() below is an immutable operation,
      // provided the query does not have any by-reference parameters.
      // This way a by-value-only query can be shared between multiple
      // threads without the need for synchronization.
      //
      if (size_t n = bind_.size ())
      {
        binding_.bind = &bind_[0];
        binding_.count = n;
        binding_.version++;
      }
    }

    query_params& query_params::
    operator= (const query_params& x)
    {
      if (this != &x)
      {
        params_ = x.params_;
        bind_ = x.bind_;

        size_t n (bind_.size ());
        binding_.bind = n != 0 ? &bind_[0] : 0;
        binding_.count = n;
        binding_.version++;
      }

      return *this;
    }

    query_params& query_params::
    operator+= (const query_params& x)
    {
      size_t n (bind_.size ());

      params_.insert (params_.end (), x.params_.begin (), x.params_.end ());
      bind_.insert (bind_.end (), x.bind_.begin (), x.bind_.end ());

      if (n != bind_.size ())
      {
        binding_.bind = &bind_[0];
        binding_.count = bind_.size ();
        binding_.version++;
      }

      return *this;
    }

    void query_params::
    add (details::shared_ptr<query_param> p)
    {
      params_.push_back (p);
      bind_.push_back (sqlite::bind ());
      binding_.bind = &bind_[0];
      binding_.count = bind_.size ();
      binding_.version++;

      sqlite::bind* b (&bind_.back ());
      memset (b, 0, sizeof (sqlite::bind));
      p->bind (b);
    }

    query_params::binding_type& query_params::
    binding ()
    {
      size_t n (params_.size ());
      binding_type& r (binding_);

      if (n == 0)
        return r;

      bool inc_ver (false);
      sqlite::bind* b (&bind_[0]);

      for (size_t i (0); i < n; ++i)
      {
        query_param& p (*params_[i]);

        if (p.reference ())
        {
          if (p.init ())
          {
            p.bind (b + i);
            inc_ver = true;
          }
        }
      }

      if (inc_ver)
        r.version++;

      return r;
    }

    // query
    //

    query::
    query (const query& q)
        : clause_ (q.clause_),
          parameters_ (new (details::shared) query_params (*q.parameters_))
    {
    }

    query& query::
    operator= (const query& q)
    {
      if (this != &q)
      {
        clause_ = q.clause_;
        *parameters_ = *q.parameters_;
      }

      return *this;
    }

    query& query::
    operator+= (const query& q)
    {
      clause_.insert (clause_.end (), q.clause_.begin (), q.clause_.end ());
      *parameters_ += *q.parameters_;
      return *this;
    }

    void query::
    append (const string& q)
    {
      if (!clause_.empty () && clause_.back ().kind == clause_part::native)
      {
        string& s (clause_.back ().part);

        char first (!q.empty () ? q[0] : ' ');
        char last (!s.empty () ? s[s.size () - 1] : ' ');

        // We don't want extra spaces after '(' as well as before ','
        // and ')'.
        //
        if (last != ' ' && last != '(' &&
            first != ' ' && first != ',' && first != ')')
          s += ' ';

        s += q;
      }
      else
        clause_.push_back (clause_part (clause_part::native, q));
    }

    void query::
    append (const char* table, const char* column)
    {
      string s ("\"");
      s += table;
      s += "\".\"";
      s += column;
      s += '"';

      clause_.push_back (clause_part (clause_part::column, s));
    }

    void query::
    add (details::shared_ptr<query_param> p)
    {
      clause_.push_back (clause_part (clause_part::param));
      parameters_->add (p);
    }

    static bool
    check_prefix (const string& s)
    {
      string::size_type n;

      // It is easier to compare to upper and lower-case versions
      // rather than getting involved with the portable case-
      // insensitive string comparison mess.
      //
      if (s.compare (0, (n = 5), "WHERE") == 0 ||
          s.compare (0, (n = 5), "where") == 0 ||
          s.compare (0, (n = 6), "SELECT") == 0 ||
          s.compare (0, (n = 6), "select") == 0 ||
          s.compare (0, (n = 8), "ORDER BY") == 0 ||
          s.compare (0, (n = 8), "order by") == 0 ||
          s.compare (0, (n = 8), "GROUP BY") == 0 ||
          s.compare (0, (n = 8), "group by") == 0 ||
          s.compare (0, (n = 6), "HAVING") == 0 ||
          s.compare (0, (n = 6), "having") == 0)
      {
        // It either has to be an exact match, or there should be
        // a whitespace following the keyword.
        //
        if (s.size () == n || s[n] == ' ' || s[n] =='\t')
          return true;
      }

      return false;
    }

    void query::
    optimize ()
    {
      // Remove a single TRUE literal or one that is followe by one of
      // the other clauses. This avoids usless WHERE clauses like
      //
      // WHERE TRUE GROUP BY foo
      //
      clause_type::iterator i (clause_.begin ()), e (clause_.end ());

      if (i != e && i->kind == clause_part::boolean && i->bool_part)
      {
        clause_type::iterator j (i + 1);

        if (j == e ||
            (j->kind == clause_part::native && check_prefix (j->part)))
          clause_.erase (i);
      }
    }

    const char* query::
    clause_prefix () const
    {
      if (!clause_.empty ())
      {
        const clause_part& p (clause_.front ());

        if (p.kind == clause_part::native && check_prefix (p.part))
          return "";

        return "WHERE ";
      }

      return "";
    }

    string query::
    clause () const
    {
      string r;

      for (clause_type::const_iterator i (clause_.begin ()),
             end (clause_.end ());
           i != end;
           ++i)
      {
        char last (!r.empty () ? r[r.size () - 1] : ' ');

        switch (i->kind)
        {
        case clause_part::column:
          {
            if (last != ' ' && last != '(')
              r += ' ';

            r += i->part;
            break;
          }
        case clause_part::param:
          {
            if (last != ' ' && last != '(')
              r += ' ';

            r += '?';
            break;
          }
        case clause_part::native:
          {
            // We don't want extra spaces after '(' as well as before ','
            // and ')'.
            //
            const string& p (i->part);
            char first (!p.empty () ? p[0] : ' ');

            if (last != ' ' && last != '(' &&
                first != ' ' && first != ',' && first != ')')
              r += ' ';

            r += p;
            break;
          }
        case clause_part::boolean:
          {
            if (last != ' ' && last != '(')
              r += ' ';

            r += i->bool_part ? "1" : "0";
            break;
          }
        }
      }

      return clause_prefix () + r;
    }

    query
    operator&& (const query& x, const query& y)
    {
      // Optimize cases where one or both sides are constant truth.
      //
      bool xt (x.const_true ()), yt (y.const_true ());

      if (xt && yt)
        return x;

      if (xt)
        return y;

      if (yt)
        return x;

      query r ("(");
      r += x;
      r += ") AND (";
      r += y;
      r += ")";
      return r;
    }

    query
    operator|| (const query& x, const query& y)
    {
      query r ("(");
      r += x;
      r += ") OR (";
      r += y;
      r += ")";
      return r;
    }

    query
    operator! (const query& x)
    {
      query r ("NOT (");
      r += x;
      r += ")";
      return r;
    }
  }
}
