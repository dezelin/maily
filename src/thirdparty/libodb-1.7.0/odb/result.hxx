// file      : odb/result.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_RESULT_HXX
#define ODB_RESULT_HXX

#include <odb/pre.hxx>

#include <cstddef>  // std::ptrdiff_t, std::size_t

#include <odb/forward.hxx> // result
#include <odb/traits.hxx>

namespace odb
{
  template <typename T, class_kind kind>
  class result_base;

  template <typename T, class_kind kind = class_traits<T>::kind>
  class result_iterator;

  // Input iterator requirements.
  //
  template <typename T, class_kind kind>
  inline bool
  operator== (result_iterator<T, kind> i, result_iterator<T, kind> j)
  {
    return i.equal (j);
  }

  template <typename T, class_kind kind>
  inline bool
  operator!= (result_iterator<T, kind> i, result_iterator<T, kind> j)
  {
    return !i.equal (j);
  }

  template <typename T>
  class result: result_base<T, class_traits<T>::kind>
  {
  public:
    static const class_kind kind = class_traits<T>::kind;

    typedef result_base<T, kind> base;

    typedef typename base::value_type value_type;
    typedef value_type*               pointer;
    typedef const value_type*         const_pointer;
    typedef value_type&               reference;
    typedef const value_type&         const_reference;

    typedef result_iterator<T, kind>  iterator;

    typedef std::size_t               size_type;
    typedef std::ptrdiff_t            difference_type;

    typedef typename base::result_impl_type result_impl_type;

  public:
    result ()
    {
    }

    explicit
    result (details::shared_ptr<result_impl_type> impl)
        : impl_ (impl)
    {
    }

    // Copying or assignment of a result instance leads to one instance
    // being an alias for another. Think of copying a result as copying
    // a file handle -- the file you access through either of them is
    // still the same.
    //
  public:
    result (const result& r)
        : impl_ (r.impl_)
    {
    }

    result&
    operator= (const result& r)
    {
      if (impl_ != r.impl_)
        impl_ = r.impl_;

      return *this;
    }

    // Conversion from result<T> to result<const T>.
    //
    template <typename UT>
    result (const result<UT>& r)
        //
        // If you get a compiler error pointing to the line below saying
        // that the impl_ member is inaccessible, then you are most likely
        // trying to perform an illegal result conversion, for example,
        // from result<const obj> to result<obj>.
        //
        : impl_ (r.impl_)
    {
    }

    template <typename UT>
    result&
    operator= (const result<UT>& r)
    {
      // If you get a compiler error pointing to the line below saying
      // that the impl_ member is inaccessible, then you are most likely
      // trying to perform an illegal result conversion, for example,
      // from result<const obj> to result<obj>.
      //
      if (impl_ != r.impl_)
        impl_ = r.impl_;

      return *this;
    }

    void
    swap (result& r)
    {
      // @@ add swap() to shared_ptr.
      //
      details::shared_ptr<result_impl_type> p (impl_);
      impl_ = r.impl_;
      r.impl_ = p;
    }

  public:
    iterator
    begin ()
    {
      if (impl_)
        impl_->begin ();

      return iterator (impl_.get ());
    }

    iterator
    end ()
    {
      return iterator ();
    }

    // Cache the result instead of fetching the data from the database
    // one row at a time. This is necessary if you plan on performing
    // database operations while iterating over the result.
    //
  public:
    void
    cache ()
    {
      if (impl_)
        impl_->cache ();
    }

  public:
    bool
    empty () const
    {
      if (impl_ == 0)
        return true;

      impl_->begin ();
      return impl_->end ();
    }

    // Size is only known in cached results.
    //
    size_type
    size () const
    {
      return impl_ ? impl_->size () : 0;
    }

  private:
    friend class result<const T>;

    details::shared_ptr<result_impl_type> impl_;
  };

  namespace core
  {
    using odb::result;
    using odb::result_iterator;
  }
}

#include <odb/post.hxx>

#endif // ODB_RESULT_HXX

// Include result specializations so that the user code only needs
// to include this header.
//

#include <odb/object-result.hxx>
#include <odb/view-result.hxx>
