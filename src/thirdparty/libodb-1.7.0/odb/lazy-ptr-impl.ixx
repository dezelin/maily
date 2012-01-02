// file      : odb/lazy-ptr-impl.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

namespace odb
{
  //
  // lazy_ptr_base
  //

  inline lazy_ptr_base::
  lazy_ptr_base ()
      : id_ (0), db_ (0)
  {
  }

  inline lazy_ptr_base::
  lazy_ptr_base (const lazy_ptr_base& r)
      : id_ (0), db_ (r.db_), free_ (r.free_), copy_ (r.copy_)
  {
    if (r.id_)
      id_ = copy_ (r.id_);
  }

  inline lazy_ptr_base::
  lazy_ptr_base (const lazy_ptr_impl_ref& r)
      : id_ (r.id_), db_ (r.db_), free_ (r.free_), copy_ (r.copy_)
  {
  }

  inline void lazy_ptr_base::
  reset_id ()
  {
    if (id_)
      free_ (id_);

    id_ = 0;
  }

  inline void lazy_ptr_base::
  reset_ (database_type* db, const void* id, free_func free, copy_func copy)
  {
    void* idc (id ? copy (id) : 0);

    if (id_)
      free_ (id_);

    free_ = free;
    copy_ = copy;

    id_ = idc;
    db_ = db;
  }

  inline void lazy_ptr_base::
  reset ()
  {
    reset_id ();
    db_ = 0;
  }

  inline void lazy_ptr_base::
  reset (database_type& db)
  {
    reset_id ();
    db_ = &db;
  }

  inline lazy_ptr_base& lazy_ptr_base::
  operator= (const lazy_ptr_base& r)
  {
    if (id_ != r.id_)
      reset_ (r.db_, r.id_, r.free_, r.copy_);
    else
      db_ = r.db_;

    return *this;
  }

  inline lazy_ptr_base& lazy_ptr_base::
  operator= (const lazy_ptr_impl_ref& r)
  {
    if (id_ != r.id_)
    {
      reset_id ();
      id_ = r.id_;
      free_ = r.free_;
      copy_ = r.copy_;
    }

    db_ = r.db_;
    return *this;
  }

  inline lazy_ptr_base::
  ~lazy_ptr_base ()
  {
    if (id_)
      free_ (id_);
  }

  inline void lazy_ptr_base::
  swap (lazy_ptr_base& r)
  {
    void* id (id_);
    database_type* db (db_);
    free_func f (free_);
    copy_func c (copy_);

    id_ = r.id_;
    db_ = r.db_;
    free_ = r.free_;
    copy_ = r.copy_;

    r.id_ = id;
    r.db_ = db;
    r.free_ = f;
    r.copy_ = c;
  }

  inline lazy_ptr_base::database_type* lazy_ptr_base::
  database () const
  {
    return db_;
  }

  inline lazy_ptr_base::
  operator lazy_ptr_impl_ref ()
  {
    lazy_ptr_impl_ref r;
    r.id_ = id_;
    r.db_ = db_;
    r.free_ = free_;
    r.copy_ = copy_;
    id_ = 0;
    db_ = 0;
    return r;
  }

  //
  // lazy_ptr_impl
  //

  template <typename T>
  inline lazy_ptr_impl<T>::
  lazy_ptr_impl ()
  {
  }

  template <typename T>
  template <typename ID>
  inline lazy_ptr_impl<T>::
  lazy_ptr_impl (database_type& db, const ID& id)
  {
    typedef typename object_traits<T>::id_type id_type;

    // Make sure that ID and T's object id types are the same
    // (or implicit-convertible). If you get a compile error
    // pointing here, then you most likely used a wrong object
    // id argument in the constructor call.
    //
    const id_type& r (id);

    reset_ (&db, &r, &free<id_type>, &copy<id_type>);
  }

  template <typename T>
  inline lazy_ptr_impl<T>::
  lazy_ptr_impl (const lazy_ptr_impl& r)
      : lazy_ptr_base (r)
  {
  }

  template <typename T>
  template <typename Y>
  inline lazy_ptr_impl<T>::
  lazy_ptr_impl (const lazy_ptr_impl<Y>& r)
      : lazy_ptr_base (r)
  {
  }

  template <typename T>
  inline lazy_ptr_impl<T>::
  lazy_ptr_impl (const lazy_ptr_impl_ref& r)
      : lazy_ptr_base (r)
  {
  }

  template <typename T>
  inline lazy_ptr_impl<T>& lazy_ptr_impl<T>::
  operator= (const lazy_ptr_impl& r)
  {
    lazy_ptr_base& b (*this);
    b = r;
    return *this;
  }

  template <typename T>
  template <typename Y>
  inline lazy_ptr_impl<T>& lazy_ptr_impl<T>::
  operator= (const lazy_ptr_impl<Y>& r)
  {
    lazy_ptr_base& b (*this);
    b = r;
    return *this;
  }

  template <typename T>
  inline lazy_ptr_impl<T>& lazy_ptr_impl<T>::
  operator= (const lazy_ptr_impl_ref& r)
  {
    lazy_ptr_base& b (*this);
    b = r;
    return *this;
  }

  template <typename T>
  template <typename ID>
  inline void lazy_ptr_impl<T>::
  reset (database_type& db, const ID& id)
  {
    typedef typename object_traits<T>::id_type id_type;

    // Make sure that ID and T's object id types are the same
    // (or implicit-convertible). If you get a compile error
    // pointing here, then you most likely used a wrong object
    // id argument in the constructor call.
    //
    const id_type& r (id);

    reset_ (&db, &r, &free<id_type>, &copy<id_type>);
  }

  template <typename T>
  template <typename ID>
  inline void lazy_ptr_impl<T>::
  reset_id (const ID& id)
  {
    typedef typename object_traits<T>::id_type id_type;

    // Make sure that ID and T's object id types are the same
    // (or implicit-convertible). If you get a compile error
    // pointing here, then you most likely used a wrong object
    // id argument in the constructor call.
    //
    const id_type& r (id);

    reset_ (db_, &r, &free<id_type>, &copy<id_type>);
  }

  template <typename T>
  template <typename O>
  inline typename object_traits<O>::id_type lazy_ptr_impl<T>::
  object_id () const
  {
    typedef typename object_traits<T>::id_type id_type;
    const id_type& id (*static_cast<const id_type*> (id_));

    // Make sure that O' and T's object id types are the same
    // (or implicit-convertible). If you get a compile error
    // pointing here, then you most likely used a wrong type
    // as a template argument in the object_id() call.
    //
    const typename object_traits<O>::id_type& r (id);
    return r;
  }
}
