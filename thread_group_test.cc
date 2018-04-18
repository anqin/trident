// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Author: qinzuoyan01 (Qin Zuoyan)

#include <gtest/gtest.h>
#include <trident/thread_group.h>
#include <trident/closure.h>

namespace trident {

class ThreadGroupTest: public ::testing::Test
{
protected:
    ThreadGroupTest() {}
    virtual ~ThreadGroupTest() {}
    virtual void SetUp() {
        // Called before every TEST_F(ThreadGroupTest, *)
    }
    virtual void TearDown() {
        // Called after every TEST_F(ThreadGroupTest, *)
    }
};

static void test_1_function(bool* called)
{
    *called = true;
}

TEST_F(ThreadGroupTest, test_1)
{
    trident::ThreadGroup* thread_group = new trident::ThreadGroup(4);

    bool dispatch_called = false;
    thread_group->dispatch(trident::NewClosure(&test_1_function, &dispatch_called));

    bool post_called = false;
    thread_group->post(trident::NewClosure(&test_1_function, &post_called));

    delete thread_group;

    ASSERT_TRUE(dispatch_called);
    ASSERT_TRUE(post_called);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

} // end trident
