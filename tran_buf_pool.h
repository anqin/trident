// Copyright (c) 2014 Baidu.com, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

#ifndef _TRIDENT_TRAN_BUF_POOL_H_
#define _TRIDENT_TRAN_BUF_POOL_H_

#include <trident/common_internal.h>

#ifndef TRIDENT_TRAN_BUF_BLOCK_SIZE
#define TRIDENT_TRAN_BUF_BLOCK_SIZE (1024u - sizeof(RefCountType))
#endif

namespace trident {


// Reference counted tran buf pool.
// Thread safe.
class TranBufPool
{
public:
    typedef int RefCountType;

    // Get the size of single block.
    inline static int block_size() 
    {
        return static_cast<int>(TRIDENT_TRAN_BUF_BLOCK_SIZE);
    }

    // Allocate a block.  Return NULL if failed.
    //
    // Postconditions:
    // * If succeed, the reference count of the block is equal to 1.
    inline static void * malloc()
    {
        void * p = ::malloc(TRIDENT_TRAN_BUF_BLOCK_SIZE + sizeof(RefCountType));
        if (p != NULL)
        {
            *(reinterpret_cast<RefCountType*>(p)) = 1;
            p = reinterpret_cast<RefCountType*>(p) + 1;
        }
        return p;
    }

    // Increase the reference count of the block.
    //
    // Preconditions:
    // * The block pointed by "p" was allocated by this pool and is in use currently.
    inline static void add_ref(void * p)
    {
        trident::atomic_inc(reinterpret_cast<RefCountType*>(p) - 1);
    }

    // Decrease the reference count of the block.  If the reference count equals
    // to 0 afterward, then put the block back to the free list
    //
    // Preconditions:
    // * The block pointed by "p" was allocated by this pool and is in use currently.
    inline static void free(void * p)
    {
        if (trident::atomic_dec_ret_old(reinterpret_cast<RefCountType*>(p) - 1) == 1)
        {
            ::free(reinterpret_cast<RefCountType*>(p) - 1);
        }
    }
}; // class TranBufPool


} // namespace trident

#endif // _TRIDENT_TRAN_BUF_POOL_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
