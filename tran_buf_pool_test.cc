// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Author: Zuoyan Qin (qinzuoyan@gmail.com)

#include <gtest/gtest.h>
#include <trident/tran_buf_pool.h>

namespace trident {

class TranBufPoolTest : public ::testing::Test {};

TEST_F(TranBufPoolTest, malloc_free_test)
{
    void* data = TranBufPool::malloc();
    ASSERT_TRUE(NULL != data);
    ASSERT_EQ(1020, TranBufPool::block_size());
    TranBufPool::free(data);
}

TEST_F(TranBufPoolTest, add_ref_test)
{
    void* data = TranBufPool::malloc();
    ASSERT_TRUE(NULL != data);
    TranBufPool::add_ref(data);
    TranBufPool::free(data);
    TranBufPool::free(data);
}
} // end trident
