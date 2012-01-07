// file      : odb/session.txx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#include <odb/pointer-traits.hxx>

namespace odb
{
  template <typename T>
  typename session::object_position<T> session::
  insert (database_type& db,
          const typename object_traits<T>::id_type& id,
          const typename object_traits<T>::pointer_type& obj)
  {
    typedef odb::object_traits<T> object_traits;
    typedef typename object_traits::pointer_type pointer_type;
    typedef odb::pointer_traits<pointer_type> pointer_traits;

    type_map& tm (db_map_[&db]);
    details::shared_ptr<object_map_base>& pom (tm[&typeid (T)]);

    if (!pom)
      pom.reset (new (details::shared) object_map<T>);

    object_map<T>& om (static_cast<object_map<T>&> (*pom));

    typename object_map<T>::value_type vt (id, obj);
    std::pair<typename object_map<T>::iterator, bool> r (om.insert (vt));

    // In what situation may we possibly attempt to reinsert the object?
    // For example, when the user loads the same object in to different
    // instances (i.e., load into a pre-allocated object). In this case
    // we should probably update our entries accordingly.
    //
    if (!r.second)
      r.first->second = obj;

    return object_position<T> (om, r.first);
  }

  template <typename T>
  typename object_traits<T>::pointer_type session::
  find (database_type& db, const typename object_traits<T>::id_type& id) const
  {
    typedef typename object_traits<T>::pointer_type pointer_type;

    database_map::const_iterator di (db_map_.find (&db));

    if (di == db_map_.end ())
      return pointer_type ();

    const type_map& tm (di->second);
    type_map::const_iterator ti (tm.find (&typeid (T)));

    if (ti == tm.end ())
      return pointer_type ();

    const object_map<T>& om (static_cast<const object_map<T>&> (*ti->second));
    typename object_map<T>::const_iterator oi (om.find (id));

    if (oi == om.end ())
      return pointer_type ();

    return oi->second;
  }

  template <typename T>
  void session::
  erase (database_type& db, const typename object_traits<T>::id_type& id)
  {
    database_map::iterator di (db_map_.find (&db));

    if (di == db_map_.end ())
      return;

    type_map& tm (di->second);
    type_map::iterator ti (tm.find (&typeid (T)));

    if (ti == tm.end ())
      return;

    object_map<T>& om (static_cast<object_map<T>&> (*ti->second));
    typename object_map<T>::iterator oi (om.find (id));

    if (oi == om.end ())
      return;

    om.erase (oi);

    if (om.empty ())
      tm.erase (ti);

    if (tm.empty ())
      db_map_.erase (di);
  }
}