// file      : odb/lazy-ptr.txx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

namespace odb
{
  //
  // lazy_ptr
  //

  template <class T>
  template <class Y>
  bool lazy_ptr<T>::
  equal (const lazy_ptr<Y>& r) const
  {
    bool t1 ((p_ == 0) == loaded ());
    bool t2 ((r.p_ == 0) == r.loaded ());

    // If both are transient, then compare the underlying pointers.
    //
    if (t1 && t2)
      return p_ == r.p_;

    // If one is transient and the other is persistent, then compare
    // the underlying pointers but only if they are non NULL. Note
    // that an unloaded persistent object is always unequal to a
    // transient object.
    //
    if (t1 || t2)
      return p_ == r.p_ && p_ != 0;

    // If both objects are persistent, then we compare databases and
    // object ids.
    //
    typedef typename object_traits<T>::object_type object_type1;
    typedef typename object_traits<Y>::object_type object_type2;

    return i_.database () == r.i_.database () &&
      object_id<object_type1> () == r.object_id<object_type2> ();
  }
}
