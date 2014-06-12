// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

#ifndef _TRIDENT_BUF_HANDLE_H_
#define _TRIDENT_BUF_HANDLE_H_

namespace trident {


struct BufHandle
{
    char* data; // block header
    int   size; // data size
    union {
        int capacity; // block capacity, used by WriteBuffer
        int offset;   // start position in the block, used by ReadBuffer
    };

    BufHandle(char* _data, int _capacity)
        : data(_data)
        , size(0)
        , capacity(_capacity) {}

    BufHandle(char* _data, int _size, int _offset)
        : data(_data)
        , size(_size)
        , offset(_offset) {}
}; // class BufHandle


} // namespace trident

#endif // _TRIDENT_BUF_HANDLE_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
