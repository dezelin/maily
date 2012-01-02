// file      : odb/sqlite/object-result.txx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#include <odb/callback.hxx>
#include <odb/exceptions.hxx>

#include <odb/sqlite/object-statements.hxx>

namespace odb
{
  namespace sqlite
  {
    //
    // object_result_impl
    //

    template <typename T>
    object_result_impl<T>::
    ~object_result_impl ()
    {
    }

    template <typename T>
    object_result_impl<T>::
    object_result_impl (const query& q,
                        details::shared_ptr<select_statement> statement,
                        object_statements<object_type>& statements)
        : base_type (statements.connection ().database ()),
          result_impl_base (q, statement),
          statements_ (statements)
    {
    }

    template <typename T>
    void object_result_impl<T>::
    load (object_type& obj, bool fetch)
    {
      if (fetch)
        load_image ();

      // This is a top-level call so the statements cannot be locked.
      //
      assert (!statements_.locked ());
      typename object_statements<object_type>::auto_lock l (statements_);

      odb::database& db (this->database ());
      object_traits::callback (db, obj, callback_event::pre_load);

      typename object_traits::image_type& i (statements_.image ());
      object_traits::init (obj, i, db);

      // Initialize the id image and binding and load the rest of the object
      // (containers, etc).
      //
      typename object_traits::id_image_type& idi (statements_.id_image ());
      object_traits::init (idi, object_traits::id (i));

      binding& idb (statements_.id_image_binding ());
      if (idi.version != statements_.id_image_version () || idb.version == 0)
      {
        object_traits::bind (idb.bind, idi);
        statements_.id_image_version (idi.version);
        idb.version++;
      }

      object_traits::load_ (statements_, obj);
      statements_.load_delayed ();
      l.unlock ();
      object_traits::callback (db, obj, callback_event::post_load);
    }

    template <typename T>
    typename object_result_impl<T>::id_type
    object_result_impl<T>::
    load_id ()
    {
      load_image ();
      return object_traits::id (statements_.image ());
    }

    template <typename T>
    void object_result_impl<T>::
    next ()
    {
      this->current (pointer_type ());

      if (!statement_->next ())
        this->end_ = true;
    }

    template <typename T>
    void object_result_impl<T>::
    load_image ()
    {
      // The image can grow between calls to load() as a result of other
      // statements execution.
      //
      typename object_traits::image_type& im (statements_.image ());

      if (im.version != statements_.select_image_version ())
      {
        binding& b (statements_.select_image_binding ());
        object_traits::bind (b.bind, im, statement_select);
        statements_.select_image_version (im.version);
        b.version++;
      }

      select_statement::result r (statement_->load ());

      if (r == select_statement::truncated)
      {
        if (object_traits::grow (im, statements_.select_image_truncated ()))
          im.version++;

        if (im.version != statements_.select_image_version ())
        {
          binding& b (statements_.select_image_binding ());
          object_traits::bind (b.bind, im, statement_select);
          statements_.select_image_version (im.version);
          b.version++;
          statement_->reload ();
        }
      }
    }

    template <typename T>
    void object_result_impl<T>::
    cache ()
    {
    }

    template <typename T>
    std::size_t object_result_impl<T>::
    size ()
    {
      throw result_not_cached ();
    }

    //
    // object_result_impl_no_id
    //

    template <typename T>
    object_result_impl_no_id<T>::
    ~object_result_impl_no_id ()
    {
    }

    template <typename T>
    object_result_impl_no_id<T>::
    object_result_impl_no_id (const query& q,
                              details::shared_ptr<select_statement> statement,
                              object_statements_no_id<object_type>& statements)
        : base_type (statements.connection ().database ()),
          result_impl_base (q, statement),
          statements_ (statements)
    {
    }

    template <typename T>
    void object_result_impl_no_id<T>::
    load (object_type& obj)
    {
      // The image can grow between calls to load() as a result of other
      // statements execution.
      //
      typename object_traits::image_type& im (statements_.image ());

      if (im.version != statements_.select_image_version ())
      {
        binding& b (statements_.select_image_binding ());
        object_traits::bind (b.bind, im, statement_select);
        statements_.select_image_version (im.version);
        b.version++;
      }

      select_statement::result r (statement_->load ());

      if (r == select_statement::truncated)
      {
        if (object_traits::grow (im, statements_.select_image_truncated ()))
          im.version++;

        if (im.version != statements_.select_image_version ())
        {
          binding& b (statements_.select_image_binding ());
          object_traits::bind (b.bind, im, statement_select);
          statements_.select_image_version (im.version);
          b.version++;
          statement_->reload ();
        }
      }

      odb::database& db (this->database ());

      object_traits::callback (db, obj, callback_event::pre_load);
      object_traits::init (obj, im, db);
      object_traits::callback (db, obj, callback_event::post_load);
    }

    template <typename T>
    void object_result_impl_no_id<T>::
    next ()
    {
      this->current (pointer_type ());

      if (!statement_->next ())
        this->end_ = true;
    }

    template <typename T>
    void object_result_impl_no_id<T>::
    cache ()
    {
    }

    template <typename T>
    std::size_t object_result_impl_no_id<T>::
    size ()
    {
      throw result_not_cached ();
    }
  }
}
