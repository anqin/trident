// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

#ifndef _TRIDENT_FAST_LOCK_H_
#define _TRIDENT_FAST_LOCK_H_

#include <trident/mutex_lock.h>
#include <trident/spin_lock.h>

namespace trident {


#if defined( TRIDENT_USE_SPINLOCK )
    typedef SpinLock FastLock;
#else
    typedef MutexLock FastLock;
#endif // defined( TRIDENT_USE_SPINLOCK )


} // namespace trident

#endif // _TRIDENT_FAST_LOCK_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
