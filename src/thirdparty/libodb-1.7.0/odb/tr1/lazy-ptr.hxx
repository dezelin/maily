// file      : odb/tr1/lazy-ptr.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_TR1_LAZY_PTR_HXX
#define ODB_TR1_LAZY_PTR_HXX

#include <odb/pre.hxx>

//
// This header assumes that the necessary TR1 header has already
// been included.
//

#include <memory> // std::auto_ptr

#include <odb/forward.hxx> // odb::database
#include <odb/traits.hxx>
#include <odb/lazy-ptr-impl.hxx>

namespace odb
{
  namespace tr1
  {
    template <class T>
    class lazy_weak_ptr;

    //
    //
    template <class T>
    class lazy_shared_ptr
    {
      // The standard shared_ptr interface.
      //
    public:
      typedef T element_type;

      lazy_shared_ptr ();
      template <class Y> explicit lazy_shared_ptr (Y*);
      template <class Y, class D> lazy_shared_ptr (Y*, D);
      template <class Y, class D, class A> lazy_shared_ptr (Y*, D, A);

      lazy_shared_ptr (const lazy_shared_ptr&);
      template <class Y> lazy_shared_ptr (const lazy_shared_ptr<Y>&);
      template <class Y> explicit lazy_shared_ptr (const lazy_weak_ptr<Y>&);
      template <class Y> explicit lazy_shared_ptr (std::auto_ptr<Y>&);

      ~lazy_shared_ptr ();

      lazy_shared_ptr& operator= (const lazy_shared_ptr&);
      template <class Y> lazy_shared_ptr& operator= (const lazy_shared_ptr<Y>&);
      template <class Y> lazy_shared_ptr& operator= (std::auto_ptr<Y>&);

      void swap (lazy_shared_ptr&);
      void reset ();
      template <class Y> void reset (Y*);
      template <class Y, class D> void reset (Y*, D);
      template <class Y, class D, class A> void reset (Y*, D, A);

      T& operator* () const;
      T* operator-> () const;
      T* get () const;

      bool unique () const;
      long use_count () const;

      typedef std::tr1::shared_ptr<T> lazy_shared_ptr::*unspecified_bool_type;
      operator unspecified_bool_type () const
      {
        return (p_ || i_) ? &lazy_shared_ptr::p_ : 0;
      }

      // Initialization/assignment from shared_ptr and weak_ptr.
      //
    public:
      template <class Y> lazy_shared_ptr (const std::tr1::shared_ptr<Y>&);
      template <class Y> explicit lazy_shared_ptr (const std::tr1::weak_ptr<Y>&);

      template <class Y> lazy_shared_ptr& operator= (const std::tr1::shared_ptr<Y>&);

      // Lazy loading interface.
      //
    public:
      typedef odb::database database_type;

      //  NULL      loaded()
      //
      //  true       true      NULL pointer to transient object
      //  false      true      valid pointer to persistent object
      //  true       false     unloaded pointer to persistent object
      //  false      false     valid pointer to transient object
      //
      bool loaded () const;

      std::tr1::shared_ptr<T> load () const;

      // Unload the pointer. For transient objects this function is
      // equivalent to reset().
      //
      void unload () const;

      template <class ID> lazy_shared_ptr (database_type&, const ID&);
      template <class Y> lazy_shared_ptr (database_type&, Y*);
      template <class Y, class D> lazy_shared_ptr (database_type&, Y*, D);
      template <class Y, class D, class A> lazy_shared_ptr (database_type&, Y*, D, A);
      template <class Y> lazy_shared_ptr (database_type&, std::auto_ptr<Y>&);
      template <class Y> lazy_shared_ptr (database_type&, const std::tr1::shared_ptr<Y>&);
      template <class Y> lazy_shared_ptr (database_type&, const std::tr1::weak_ptr<Y>&);

      template <class ID> void reset (database_type&, const ID&);
      template <class Y> void reset (database_type&, Y*);
      template <class Y, class D> void reset (database_type&, Y*, D);
      template <class Y, class D, class A> void reset (database_type&, Y*, D, A);
      template <class Y> void reset (database_type&, const std::auto_ptr<Y>&);
      template <class Y> void reset (database_type&, const std::tr1::shared_ptr<Y>&);

      template <class O /* = T */>
      typename object_traits<O>::id_type object_id () const;

      database_type& database () const;

      // Helpers.
      //
    public:
      template <class Y> bool equal (const lazy_shared_ptr<Y>&) const;

    private:
      template <class Y> friend class lazy_shared_ptr;
      template <class Y> friend class lazy_weak_ptr;

      mutable std::tr1::shared_ptr<T> p_;
      mutable lazy_ptr_impl<T> i_;
    };

    // operator< and operator<< are not provided.
    //
    template<class T, class Y>
    bool operator== (const lazy_shared_ptr<T>&, const lazy_shared_ptr<Y>&);

    template<class T, class Y>
    bool operator!= (const lazy_shared_ptr<T>&, const lazy_shared_ptr<Y>&);

    template<class T> void swap (lazy_shared_ptr<T>&, lazy_shared_ptr<T>&);

    template<class D, class T>
    D* get_deleter (const lazy_shared_ptr<T>&);

    //
    //
    template <class T>
    class lazy_weak_ptr
    {
      // The standard weak_ptr interface.
      //
    public:
      typedef T element_type;

      lazy_weak_ptr ();
      template <class Y> lazy_weak_ptr (const lazy_shared_ptr<Y>&);
      lazy_weak_ptr (const lazy_weak_ptr&);
      template <class Y> lazy_weak_ptr (const lazy_weak_ptr<Y>&);

      ~lazy_weak_ptr ();

      lazy_weak_ptr& operator= (const lazy_weak_ptr&);
      template <class Y> lazy_weak_ptr& operator= (const lazy_weak_ptr<Y>&);
      template <class Y> lazy_weak_ptr& operator= (const lazy_shared_ptr<Y>&);

      void swap (lazy_weak_ptr<T>&);
      void reset ();

      long use_count () const;
      bool expired () const;

      lazy_shared_ptr<T> lock () const;

      // Initialization/assignment from shared_ptr and weak_ptr.
      //
    public:
      template <class Y> lazy_weak_ptr (const std::tr1::weak_ptr<Y>&);
      template <class Y> lazy_weak_ptr (const std::tr1::shared_ptr<Y>&);

      template <class Y> lazy_weak_ptr& operator= (const std::tr1::weak_ptr<Y>&);
      template <class Y> lazy_weak_ptr& operator= (const std::tr1::shared_ptr<Y>&);

      // Lazy loading interface.
      //
    public:
      typedef odb::database database_type;

      // expired()  loaded()
      //
      //  true       true      expired pointer to transient object
      //  false      true      valid pointer to persistent object
      //  true       false     expired pointer to persistent object
      //  false      false     valid pointer to transient object
      //
      bool loaded () const;

      // Performs both lock and load.
      //
      std::tr1::shared_ptr<T> load () const;

      // Unload the pointer. For transient objects this function is
      // equivalent to reset().
      //
      void unload () const;

      template <class ID> lazy_weak_ptr (database_type&, const ID&);
      template <class Y> lazy_weak_ptr (database_type&, const std::tr1::shared_ptr<Y>&);
      template <class Y> lazy_weak_ptr (database_type&, const std::tr1::weak_ptr<Y>&);

      template <class ID> void reset (database_type&, const ID&);
      template <class Y> void reset (database_type&, const std::tr1::shared_ptr<Y>&);
      template <class Y> void reset (database_type&, const std::tr1::weak_ptr<Y>&);

      // The object_id() function can only be called when the object is
      // persistent, or: expired() XOR loaded() (can use != for XOR).
      //
      template <class O /* = T */>
      typename object_traits<O>::id_type object_id () const;

      database_type& database () const;

    private:
      template <class Y> friend class lazy_shared_ptr;
      template <class Y> friend class lazy_weak_ptr;

      mutable std::tr1::weak_ptr<T> p_;
      mutable lazy_ptr_impl<T> i_;
    };

    // operator< is not provided.
    //
    template<class T> void swap (lazy_weak_ptr<T>&, lazy_weak_ptr<T>&);
  }
}

#include <odb/tr1/lazy-ptr.ixx>
#include <odb/tr1/lazy-ptr.txx>

#include <odb/tr1/lazy-pointer-traits.hxx>

#include <odb/post.hxx>

#endif // ODB_TR1_LAZY_PTR_HXX
