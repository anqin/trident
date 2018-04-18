// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Author: Zuoyan Qin (qinzuoyan@gmail.com)

#include <gtest/gtest.h>
#include <trident/atomic.h>

namespace trident {

class AtomicTest: public ::testing::Test {};

TEST_F(AtomicTest, test)
{
    const int g = 1024 * 1024 * 1024;
    int a = 10;
    ASSERT_EQ(10, atomic_add_ret_old(&a, 5));
    ASSERT_EQ(15, a);
    ASSERT_EQ(15, atomic_add_ret_old(&a, -10));
    ASSERT_EQ(5, a);
    ASSERT_EQ(5, atomic_add_ret_old(&a, -5));
    ASSERT_EQ(0, a);
    ASSERT_EQ(0, atomic_add_ret_old(&a, -5));
    ASSERT_EQ(-5, a);
    ASSERT_EQ(-5, atomic_add_ret_old(&a, 5));
    ASSERT_EQ(0, a);
    ASSERT_EQ(0, atomic_add_ret_old(&a, g));
    ASSERT_EQ(g, a);
    ASSERT_EQ(g, atomic_add_ret_old(&a, -g * 2));
    ASSERT_EQ(-g, a);

    ASSERT_EQ(-g, atomic_swap(&a, 0));
    ASSERT_EQ(0, a);

    ASSERT_EQ(0, atomic_comp_swap(&a, 1, 1));
    ASSERT_EQ(0, a);

    ASSERT_EQ(0, atomic_comp_swap(&a, 1, 0));
    ASSERT_EQ(1, a);
}

} // trident
