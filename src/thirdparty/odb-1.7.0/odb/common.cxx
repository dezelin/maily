// file      : odb/common.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v3; see accompanying LICENSE file

#include <odb/common.hxx>

using namespace std;

//
// object_members_base
//

void object_members_base::
traverse_simple (semantics::data_member&)
{
}

void object_members_base::
traverse_composite (semantics::data_member*, semantics::class_& c)
{
  inherits (c);
  names (c);
}

void object_members_base::
traverse_composite_wrapper (semantics::data_member* m,
                            semantics::class_& c,
                            semantics::type*)
{
  traverse_composite (m, c);
}

void object_members_base::
traverse_container (semantics::data_member&, semantics::type&)
{
}

void object_members_base::
traverse_object (semantics::class_& c)
{
  inherits (c);
  names (c);
}

void object_members_base::
traverse_view (semantics::class_& c)
{
  // A view has no bases.
  //
  names (c);
}

void object_members_base::
traverse (semantics::data_member& m, semantics::class_& c)
{
  // We are starting from the member. Add an empty chain which
  // corresponds to the scope that contains this member.
  //
  //member_scope_.push_back (class_inheritance_chain ());
  //member_path_.push_back (&m);

  member_scope_.push_back (class_inheritance_chain ());
  member_scope_.back ().push_back (&c);

  traverse_composite_wrapper (&m, c, 0);

  member_scope_.pop_back ();

  //member_path_.pop_back ();
  //member_scope_.pop_back ();
}

void object_members_base::
traverse (semantics::class_& c)
{
  class_kind_type k (class_kind (c));

  if (k == class_other)
  {
    // Ignore transient bases.
    //
    assert (context::top_object != 0);
    return;
  }
  else if (k == class_composite)
  {
    if (member_scope_.empty ())
      member_scope_.push_back (class_inheritance_chain ());

    member_scope_.back ().push_back (&c);

    traverse_composite_wrapper (0, c, 0);

    member_scope_.back ().pop_back ();

    if (member_scope_.back ().empty ())
      member_scope_.pop_back ();

    return;
  }

  semantics::class_* prev (context::cur_object);
  context::cur_object = &c;

  if (context::top_object == 0)
    context::top_object = &c;

  if (member_scope_.empty ())
    member_scope_.push_back (class_inheritance_chain ());

  member_scope_.back ().push_back (&c);

  if (build_table_prefix_)
  {
    // Don't reset the table prefix if we are traversing a base.
    //
    bool tb (false);

    if (table_prefix_.level == 0)
    {
      table_prefix_.prefix = table_name (c);
      table_prefix_.prefix += '_';
      table_prefix_.level = 1;
      tb = true;
    }

    if (k == class_object)
      traverse_object (c);
    else
      traverse_view (c);

    if (tb)
    {
      table_prefix_.level = 0;
      table_prefix_.prefix.clear ();
    }
  }
  else
  {
    if (k == class_object)
      traverse_object (c);
    else
      traverse_view (c);
  }

  member_scope_.back ().pop_back ();

  if (member_scope_.back ().empty ())
    member_scope_.pop_back ();

  if (prev == 0)
    context::top_object = 0;

  context::cur_object = prev;
}

void object_members_base::member::
traverse (semantics::data_member& m)
{
  if (transient (m))
    return;

  om_.member_path_.push_back (&m);

  semantics::type& t (utype (m));

  if (semantics::class_* comp = context::composite_wrapper (t))
  {
    om_.member_scope_.push_back (class_inheritance_chain ());
    om_.member_scope_.back ().push_back (comp);

    string old_flat_prefix, old_table_prefix, old_member_prefix;

    if (om_.build_flat_prefix_)
    {
      old_flat_prefix = om_.flat_prefix_;
      om_.flat_prefix_ += om_.public_name (m);
      om_.flat_prefix_ += '_';
    }

    if (om_.build_member_prefix_)
    {
      old_member_prefix = om_.member_prefix_;
      om_.member_prefix_ += m.name ();
      om_.member_prefix_ += '.';
    }

    if (om_.build_table_prefix_)
    {
      old_table_prefix = om_.table_prefix_.prefix;
      append (m, om_.table_prefix_);
    }

    om_.traverse_composite_wrapper (&m, *comp, (wrapper (t) ? &t : 0));

    if (om_.build_table_prefix_)
    {
      om_.table_prefix_.level--;
      om_.table_prefix_.prefix = old_table_prefix;
    }

    if (om_.build_flat_prefix_)
      om_.flat_prefix_ = old_flat_prefix;

    if (om_.build_member_prefix_)
      om_.member_prefix_ = old_member_prefix;

    om_.member_scope_.pop_back ();
  }
  else if (semantics::type* c = context::container (m))
  {
    om_.traverse_container (m, *c);
  }
  else
  {
    om_.traverse_simple (m);
  }

  om_.member_path_.pop_back ();
}

void object_members_base::
append (semantics::data_member& m, table_prefix& tp)
{
  context& ctx (context::current ());

  // If the user provided a table prefix, then use it verbatim. Also
  // drop the top-level table prefix in this case.
  //
  if (m.count ("table"))
  {
    if (tp.level <= 1)
      tp.prefix = ctx.options.table_prefix ();

    tp.prefix += m.get<string> ("table");
  }
  // Otherwise use the member name and add an underscore unless it is
  // already there.
  //
  else
  {
    string name (ctx.public_name_db (m));
    size_t n (name.size ());

    if (tp.prefix.empty ())
      tp.prefix = ctx.options.table_prefix ();

    tp.prefix += name;

    if (n != 0 && name[n - 1] != '_')
      tp.prefix += '_';
  }

  tp.level++;
}

//
// object_columns_base
//

void object_columns_base::
flush ()
{
}

void object_columns_base::
traverse_composite (semantics::data_member*, semantics::class_& c)
{
  inherits (c);
  names (c);
}

void object_columns_base::
traverse_object (semantics::class_& c)
{
  inherits (c);
  names (c);
}

void object_columns_base::
traverse_view (semantics::class_& c)
{
  // A view has no bases.
  //
  names (c);
}

void object_columns_base::
traverse (semantics::data_member& m,
          semantics::class_& c,
          string const& key_prefix,
          string const& default_name)
{
  // We are starting from the member. Add an empty chain which
  // corresponds to the scope that contains this member.
  //
  //member_scope_.push_back (class_inheritance_chain ());
  //member_path_.push_back (&m);

  member_scope_.push_back (class_inheritance_chain ());
  member_scope_.back ().push_back (&c);

  column_prefix_ = column_prefix (m, key_prefix, default_name);

  traverse_composite (&m, c);

  if (!member_.first_)
    flush ();

  member_scope_.pop_back ();

  //member_path_.pop_back ();
  //member_scope_.pop_back ();
}

void object_columns_base::
traverse (semantics::class_& c)
{
  class_kind_type k (class_kind (c));

  // Ignore transient bases.
  //
  if (k == class_other)
  {
    assert (context::top_object != 0);
    return;
  }

  bool f (top_level_);

  if (top_level_)
    top_level_ = false;

  semantics::class_* prev;
  if (k == class_object || k == class_view)
  {
    prev = context::cur_object;
    context::cur_object = &c;

    if (context::top_object == 0)
      context::top_object = &c;
  }

  if (member_scope_.empty ())
    member_scope_.push_back (class_inheritance_chain ());

  member_scope_.back ().push_back (&c);

  if (k == class_object)
    traverse_object (c);
  else if (k == class_view)
    traverse_view (c);
  else if (k == class_composite)
    traverse_composite (0, c);

  member_scope_.back ().pop_back ();

  if (member_scope_.back ().empty ())
    member_scope_.pop_back ();

  if (k == class_object || k == class_view)
  {
    if (prev == 0)
      context::top_object = 0;

    context::cur_object = prev;
  }

  if (f && !member_.first_)
    flush ();
}

string object_columns_base::
column_prefix (semantics::data_member& m, string const& kp, string const& dn)
{
  bool custom;
  string r;

  if (kp.empty ())
  {
    custom = m.count ("column");
    r = context::current ().column_name (m);
  }
  else
  {
    custom = m.count (kp + "-column");
    r = context::current ().column_name (m, kp, dn);
  }

  // If the user provided the column prefix, then use it verbatime.
  // Otherwise, append the underscore, unless it is already there.
  //
  if (!custom)
  {
    size_t n (r.size ());

    if (n != 0 && r[n - 1] != '_')
      r += '_';
  }

  return r;
}

void object_columns_base::member::
traverse (semantics::data_member& m)
{
  if (transient (m))
    return;

  oc_.member_path_.push_back (&m);

  semantics::type& t (utype (m));

  if (semantics::class_* comp = composite_wrapper (t))
  {
    oc_.member_scope_.push_back (class_inheritance_chain ());
    oc_.member_scope_.back ().push_back (comp);

    string old_prefix (oc_.column_prefix_);
    oc_.column_prefix_ += column_prefix (m);

    oc_.traverse_composite (&m, *comp);

    oc_.column_prefix_ = old_prefix;

    oc_.member_scope_.pop_back ();
  }
  else if (container (m))
  {
    // Container gets its own table, so nothing to do here.
    //
  }
  else
  {
    if (oc_.traverse_column (m, oc_.column_prefix_ + column_name (m), first_))
    {
      if (first_)
        first_ = false;
    }
  }

  oc_.member_path_.pop_back ();
}
