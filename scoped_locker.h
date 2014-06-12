// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

#ifndef _TRIDENT_SCOPED_LOCKER_H_
#define _TRIDENT_SCOPED_LOCKER_H_

namespace trident {


template <typename LockType>
class ScopedLocker
{
public:
    explicit ScopedLocker(LockType& lock)
        : _lock(&lock)
    {
        _lock->lock();
    }

    explicit ScopedLocker(LockType* lock)
        : _lock(lock)
    {
        _lock->lock();
    }

    ~ScopedLocker()
    {
        _lock->unlock();
    }

private:
    LockType* _lock;
}; // class ScopedLocker


} // namespace trident

#endif // _TRIDENT_SCOPED_LOCKER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
