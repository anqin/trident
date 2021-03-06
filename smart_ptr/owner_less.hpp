// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

// This file is modified from boost.
//
// Copyright Beman Dawes 2002, 2006
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See library home page at http://www.boost.org/libs/system

#ifndef _TRIDENT_SMART_PTR_OWNER_LESS_
#define _TRIDENT_SMART_PTR_OWNER_LESS_

#include <functional>

namespace trident {


  template<typename T> class shared_ptr;
  template<typename T> class weak_ptr;

  namespace detail
  {
    template<typename T, typename U>
      struct generic_owner_less : public std::binary_function<T, T, bool>
    {
      bool operator()(const T &lhs, const T &rhs) const
      {
        return lhs.owner_before(rhs);
      }
      bool operator()(const T &lhs, const U &rhs) const
      {
        return lhs.owner_before(rhs);
      }
      bool operator()(const U &lhs, const T &rhs) const
      {
        return lhs.owner_before(rhs);
      }
    };
  } // namespace detail

  template<typename T> struct owner_less;

  template<typename T>
    struct owner_less<shared_ptr<T> >:
    public detail::generic_owner_less<shared_ptr<T>, weak_ptr<T> >
  {};

  template<typename T>
    struct owner_less<weak_ptr<T> >:
    public detail::generic_owner_less<weak_ptr<T>, shared_ptr<T> >
  {};


} // namespace trident

#endif // _TRIDENT_SMART_PTR_OWNER_LESS_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
