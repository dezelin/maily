// file      : odb/context.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v3; see accompanying LICENSE file

#ifndef ODB_CONTEXT_HXX
#define ODB_CONTEXT_HXX

#include <odb/gcc-fwd.hxx>

#include <map>
#include <set>
#include <stack>
#include <vector>
#include <string>
#include <memory>  // std::auto_ptr
#include <ostream>
#include <cstddef> // std::size_t
#include <iostream>

#include <cutl/re.hxx>
#include <cutl/shared-ptr.hxx>

#include <odb/options.hxx>
#include <odb/cxx-token.hxx>
#include <odb/semantics.hxx>
#include <odb/semantics/relational/model.hxx>
#include <odb/traversal.hxx>

using std::endl;
using std::cerr;

// Regex.
//
using cutl::re::regex;
using cutl::re::regexsub;

typedef std::vector<regexsub> regex_mapping;

//
//
class operation_failed {};

// Keep this enum synchronized with the one in libodb/odb/pointer-traits.hxx.
//
enum pointer_kind
{
  pk_raw,
  pk_unique,
  pk_shared,
  pk_weak
};

// Keep this enum synchronized with the one in libodb/odb/container-traits.hxx.
//
enum container_kind
{
  ck_ordered,
  ck_set,
  ck_multiset,
  ck_map,
  ck_multimap
};

// The same as class_kind in libodb/odb/traits.hxx.
//
enum class_kind
{
  class_object,
  class_view,
  class_composite,
  class_other
};

// Data member path.
//
// If it is a direct member of an object, then we will have just
// one member. However, if this is a member inside a composite
// value, then we will have a "path" constructed out of members
// that lead all the way from the object member to the innermost
// composite value member.
//
typedef std::vector<semantics::data_member*> data_member_path;

// Class inheritance chain, from the most derived to base.
//
typedef std::vector<semantics::class_*> class_inheritance_chain;

// A list of inheritance chains for a data member in an object.
// The first entry in this list would correspond to the object.
// All subsequent entries, if any, correspond to composite
// values.
//
typedef std::vector<class_inheritance_chain> data_member_scope;

//
// Semantic graph context types.
//

// Object or view pointer.
//
struct class_pointer
{
  std::string name;
  tree scope;
  location_t loc;
};

//
//
struct default_value
{
  enum kind_type
  {
    reset,   // Default value reset.
    null,
    boolean,
    number,  // Integer of floating-point number. Value contains sign.
    string,
    enumerator // Value is the name, node is the tree node.
  };

  kind_type kind;
  std::string value;
  tree node;
};

// Object or table associated with the view.
//
struct view_object
{
  // Return an alias or unqualified object name.
  //
  std::string
  name () const
  {
    if (!alias.empty ())
      return alias;

    return kind == object ? obj->name () : orig_name;
  }

  enum kind_type { object, table };

  kind_type kind;
  tree node;              // Tree node if kind is object.
  std::string orig_name;  // Original name as specified in the pragma.
  std::string alias;
  tree scope;
  location_t loc;
  semantics::class_* obj;

  cxx_tokens cond; // Join condition tokens.
};

typedef std::vector<view_object> view_objects;

// The view_alias_map does not contain entries for tables.
//
typedef std::map<std::string, view_object*> view_alias_map;
typedef std::map<tree, view_object*> view_object_map;

//
//
struct view_query
{
  enum kind_type
  {
    runtime,
    complete,
    condition
  };

  kind_type kind;
  std::string literal;
  cxx_tokens expr;
  tree scope;
  location_t loc;
};

//
//
struct table_column
{
  std::string table;
  std::string column;
  bool expr; // True if column is an expression, and therefore should not
             // be quoted.
};

//
//
struct column_expr_part
{
  enum kind_type
  {
    literal,
    reference
  };

  kind_type kind;
  std::string value;
  std::string table;            // Table name/alias for references.
  data_member_path member_path; // Path to member for references.

  // Scope and location of this pragma. Used to resolve the member name.
  //
  tree scope;
  location_t loc;
};

struct column_expr: std::vector<column_expr_part>
{
  location_t loc;
};

class context
{
public:
  typedef std::size_t size_t;
  typedef std::string string;
  typedef std::vector<string> strings;
  typedef std::ostream ostream;

  typedef ::options options_type;

  static string
  upcase (string const&);

public:
  // Return cvr-unqualified base of the type, or type itself, if it is
  // not qualified.
  //
  static semantics::type&
  utype (semantics::type&);

  // The same as above, but also returns the name hint for the unqualified
  // type. If the original type is already unqualified, then the hint
  // argument is not modified.
  //
  static semantics::type&
  utype (semantics::type&, semantics::names*& hint);

  // The same for a member's type.
  //
  static semantics::type&
  utype (semantics::data_member& m)
  {
    return utype (m.type ());
  }

  // In addition to the unqualified type, this version also returns the
  // name hint for this type. If the member type is already unqualified,
  // then the hint is from the belongs edge. Otherwise, it is from the
  // qualifies edge.
  //
  static semantics::type&
  utype (semantics::data_member&, semantics::names*& hint);

  static bool
  const_type (semantics::type&);

  static semantics::type&
  member_type (semantics::data_member& m, string const& key_prefix);

  static semantics::type&
  member_utype (semantics::data_member& m, string const& key_prefix)
  {
    return utype (member_type (m, key_prefix));
  }

  // Predicates.
  //
public:
  static bool
  object (semantics::type& t)
  {
    return t.count ("object");
  }

  static bool
  view (semantics::type& t)
  {
    return t.count ("view");
  }

  // Check whether the type is a wrapper. Return the wrapped type if
  // it is a wrapper and NULL otherwise. Note that the returned type
  // may be cvr-qualified.
  //
  static semantics::type*
  wrapper (semantics::type& t)
  {
    return t.count ("wrapper") && t.get<bool> ("wrapper")
      ? t.get<semantics::type*> ("wrapper-type")
      : 0;
  }

  // Composite value type is a class type that was explicitly marked
  // as value type and there was no database type mapping provided for
  // it by the user (specifying the database type makes the value type
  // simple).
  //
  static bool
  composite (semantics::class_& c)
  {
    if (c.count ("composite-value"))
      return c.get<bool> ("composite-value");
    else
      return composite_ (c);
  }

  // Return the class object if this type is a composite value type
  // and NULL otherwise.
  //
  static semantics::class_*
  composite (semantics::type& t)
  {
    semantics::class_* c (dynamic_cast<semantics::class_*> (&t));
    return c != 0 && composite (*c) ? c : 0;
  }

  // As above but also "sees through" wrappers.
  //
  static semantics::class_*
  composite_wrapper (semantics::type& t)
  {
    if (semantics::class_* c = composite (t))
      return c;
    else if (semantics::type* wt = wrapper (t))
      return composite (utype (*wt));
    else
      return 0;
  }

  // Check if a data member is a container. "Sees through" wrappers and
  // returns the actual container type or NULL if not a container.
  //
  // We require data member as input instead of the type because the
  // same type (e.g., vector<char>) can be used for both container
  // and simple value members.
  //
  static semantics::type*
  container (semantics::data_member& m)
  {
    // The same type can be used as both a container and a simple value.
    // If the member has defines the database type, then it is the latter.
    //
    if (m.count ("type") || m.count ("id-type"))
      return 0;

    semantics::type* t (&utype (m));

    if (semantics::type* wt = wrapper (*t))
      t = &utype (*wt);

    return t->count ("container-kind") ? t : 0;
  }

  static semantics::class_*
  object_pointer (semantics::type& t)
  {
    return t.get<semantics::class_*> ("element-type", 0);
  }

  static bool
  abstract (semantics::class_& c)
  {
    // If a class is abstract in the C++ sense then it is also abstract in
    // the database sense.
    //
    return c.abstract () || c.count ("abstract");
  }

  static bool
  transient (semantics::data_member& m)
  {
    return m.count ("transient");
  }

  static bool
  id (semantics::data_member& m)
  {
    return m.count ("id");
  }

  // The member scope is used to override readonly status when a readonly
  // class (object or composite value) inherits from a readwrite base.
  //
  static bool
  readonly (data_member_path const&, data_member_scope const&);

  static bool
  readonly (semantics::data_member&);

  static bool
  readonly (semantics::class_& c)
  {
    return c.count ("readonly");
  }

  //
  //
  bool
  null (semantics::data_member&);

  bool
  null (semantics::data_member&, string const& key_prefix);

  // Optimistic concurrency.
  //
  static semantics::data_member*
  optimistic (semantics::class_& c)
  {
    // Set by the validator.
    //
    return c.get<semantics::data_member*> ("optimistic-member", 0);
  }

  static bool
  version (semantics::data_member& m)
  {
    return m.count ("version");
  }

  //
  //
  typedef ::class_kind class_kind_type;

  static class_kind_type
  class_kind (semantics::class_&);

  // Database names and types.
  //
public:
  string
  table_name (semantics::class_&) const;

  string
  table_name (semantics::class_&, data_member_path const&) const;

  struct table_prefix
  {
    table_prefix (): level (0) {}
    table_prefix (string const& p, size_t l): prefix (p), level (l) {}

    string prefix;
    size_t level;
  };

  // Table name for the container member. The table prefix passed as the
  // second argument must include the table prefix specified with the
  // --table-prefix option.
  //
  string
  table_name (semantics::data_member&, table_prefix const&) const;

  string
  column_name (semantics::data_member&) const;

  string
  column_name (data_member_path const&) const;

  string
  column_name (semantics::data_member&,
               string const& key_prefix,
               string const& default_name) const;

  string
  column_type (semantics::data_member&, string const& key_prefix = string ());

  string
  column_options (semantics::data_member&);

  string
  column_options (semantics::data_member&, string const& key_prefix);

  // Cleaned-up member name that can be used for database names.
  //
  string
  public_name_db (semantics::data_member&) const;

  // C++ names.
  //
public:
  // Cleaned-up and escaped member name that can be used in public C++
  // interfaces.
  //
  string
  public_name (semantics::data_member&) const;

  // "Flatten" fully-qualified C++ name by replacing '::' with '_'
  // and removing leading '::', if any.
  //
  static string
  flat_name (string const& fqname);

  // Escape C++ keywords, reserved names, and illegal characters.
  //
  string
  escape (string const&) const;

  // Return a string literal that can be used in C++ source code. It
  // includes "".
  //
  string
  strlit (string const&);

  // Counts and other information.
  //
public:
  struct column_count_type
  {
    column_count_type ()
        : total (0),
          id (0),
          inverse (0),
          readonly (0),
          optimistic_managed (0)
    {
    }

    size_t total;
    size_t id;
    size_t inverse;
    size_t readonly;
    size_t optimistic_managed;
  };

  static column_count_type
  column_count (semantics::class_&);

  static semantics::data_member*
  id_member (semantics::class_& c)
  {
    // Set by the validator. May not be there for abstract objects.
    //
    return c.get<semantics::data_member*> ("id-member", 0);
  }

  // Object pointer information.
  //
public:
  typedef ::pointer_kind pointer_kind_type;

  pointer_kind_type
  pointer_kind (semantics::type& p)
  {
    return p.get<pointer_kind_type> ("pointer-kind");
  }

  bool
  lazy_pointer (semantics::type& p)
  {
    return p.get<bool> ("pointer-lazy");
  }

  bool
  weak_pointer (semantics::type& p)
  {
    return pointer_kind (p) == pk_weak;
  }

  static semantics::data_member*
  inverse (semantics::data_member& m)
  {
    return object_pointer (utype (m))
      ? m.get<semantics::data_member*> ("inverse", 0)
      : 0;
  }

  semantics::data_member*
  inverse (semantics::data_member& m, string const& key_prefix)
  {
    if (key_prefix.empty ())
      return inverse (m);

    return object_pointer (member_utype (m, key_prefix))
      ? m.get<semantics::data_member*> (key_prefix + "-inverse", 0)
      : 0;
  }

  // Container information.
  //
public:
  typedef ::container_kind container_kind_type;

  static container_kind_type
  container_kind (semantics::type& c)
  {
    return c.get<container_kind_type> ("container-kind");
  }

  static semantics::type&
  container_idt (semantics::data_member& m)
  {
    return member_utype (m, "id");
  }

  static semantics::type&
  container_vt (semantics::type& c)
  {
    return *c.get<semantics::type*> ("value-tree-type");
  }

  static semantics::type&
  container_it (semantics::type& c)
  {
    return *c.get<semantics::type*> ("index-tree-type");
  }

  static semantics::type&
  container_kt (semantics::type& c)
  {
    return *c.get<semantics::type*> ("key-tree-type");
  }

  static bool
  unordered (semantics::data_member& m)
  {
    if (m.count ("unordered"))
      return true;

    if (semantics::type* c = container (m))
      return c->count ("unordered");

    return false;
  }

  // The 'is a' and 'has a' tests. The has_a test currently does not
  // cross the container boundaries.
  //
public:
  static unsigned short const test_pointer = 0x01;
  static unsigned short const test_eager_pointer = 0x02;
  static unsigned short const test_lazy_pointer = 0x04;
  static unsigned short const test_container = 0x08;
  static unsigned short const test_straight_container = 0x10;
  static unsigned short const test_inverse_container = 0x20;
  static unsigned short const test_readonly_container = 0x40;

  static unsigned short const exclude_base = 0x8000;

  bool
  is_a (data_member_path const& mp,
        data_member_scope const& ms,
        unsigned short flags)
  {
    return is_a (mp, ms, flags, utype (*mp.back ()), "");
  }

  bool
  is_a (data_member_path const&,
        data_member_scope const&,
        unsigned short flags,
        semantics::type&,
        string const& key_prefix);

  // Return the number of matching entities. Can be uses as a just
  // a bool value (0 means no match).
  //
  size_t
  has_a (semantics::class_&, unsigned short flags);

public:
  // Process include path by adding the prefix, putting it through
  // the include regex list, and adding opening and closing include
  // characters ("" or <>) if necessary. The prefix argument indicates
  // whether the include prefix specified with the --include-prefix
  // option should be added. The open argument can be used to specify
  // the opening character. It can have three values: ", <, or \0. In
  // case of \0, the character is determined based on the value of the
  // --include-with-bracket option.
  //
  string
  process_include_path (string const&, bool prefix = true, char open = '\0');

  // Diverge output.
  //
public:
  void
  diverge (std::ostream& os)
  {
    diverge (os.rdbuf ());
  }

  void
  diverge (std::streambuf* sb);

  void
  restore ();

  // Implementation details.
  //
private:
  static bool
  composite_ (semantics::class_&);

  template <typename X>
  static X
  indirect_value (semantics::context const& c, string const& key)
  {
    typedef X (*func) ();
    std::type_info const& ti (c.type_info (key));

    if (ti == typeid (func))
      return c.get<func> (key) ();
    else
      return c.get<X> (key);
  }

public:
  typedef std::set<string> keyword_set_type;

  struct db_type_type
  {
    db_type_type () {}
    db_type_type (string const& t, string const& it)
        : type (t), id_type (it)
    {
    }

    string type;
    string id_type;
  };
  typedef std::map<string, db_type_type> type_map_type;

protected:
  struct data
  {
    virtual
    ~data () {}
    data (std::ostream& os)
        : os_ (os.rdbuf ()), top_object_ (0), cur_object_ (0)
    {
    }

  public:
    std::ostream os_;
    std::stack<std::streambuf*> os_stack_;

    semantics::class_* top_object_;
    semantics::class_* cur_object_;

    keyword_set_type keyword_set_;
    type_map_type type_map_;

    regex_mapping include_regex_;
  };

  typedef cutl::shared_ptr<data> data_ptr;
  data_ptr data_;

public:
  std::ostream& os;
  semantics::unit& unit;
  options_type const& options;
  database const db;

  keyword_set_type const& keyword_set;

  regex_mapping const& include_regex;

  bool embedded_schema;

  // Outermost object or view currently being traversed.
  //
  semantics::class_*& top_object;

  // Object or view currently being traversed. It can be the same as
  // top_object or it can a base of top_object.
  //
  semantics::class_*& cur_object;

  // Per-database customizable functionality.
  //
protected:
  // Return empty string if there is no mapping.
  //
  string
  database_type (semantics::type& t, semantics::names* hint, bool id)
  {
    return current ().database_type_impl (t, hint, id);
  }

  // The default implementation uses the type map (populated by the database-
  // specific context implementation) to come up with a mapping.
  //
  virtual string
  database_type_impl (semantics::type&, semantics::names*, bool);

public:
  typedef context root_context;

  virtual
  ~context ();
  context ();
  context (std::ostream&,
           semantics::unit&,
           options_type const&,
           data_ptr = data_ptr ());

  static context&
  current ()
  {
    return *current_;
  }

private:
  static context* current_;

private:
  context&
  operator= (context const&);
};

// Create concrete database context.
//
std::auto_ptr<context>
create_context (std::ostream&,
                semantics::unit&,
                options const&,
                semantics::relational::model*);

// Checks if scope Y names any of X.
//
template <typename X, typename Y>
bool
has (Y& y)
{
  for (semantics::scope::names_iterator i (y.names_begin ()),
         e (y.names_end ()); i != e; ++i)
    if (i->named (). template is_a<X> ())
      return true;

  return false;
}

// Standard namespace traverser.
//
struct namespace_: traversal::namespace_, context
{
  virtual void
  traverse (type&);
};

#endif // ODB_CONTEXT_HXX
