// Copyright (c) 2014 Baidu.com, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Author: qinzuoyan01@baidu.com (Qin Zuoyan)

#include <trident/mock_test_helper.h>
#include <trident/mock_test_helper_impl.h>

namespace trident {


MockTestHelper::MockTestHelper() {}
MockTestHelper::~MockTestHelper() {}

MockTestHelper* MockTestHelper::GlobalInstance()
{
    static MockTestHelperImpl s_mock_channel;
    return &s_mock_channel;
}

bool g_enable_mock = false;

void enable_mock()
{
    MockTestHelper::GlobalInstance();
    g_enable_mock = true;
}

void disable_mock()
{
    g_enable_mock = false;
}


} // namespace trident

/* vim: set ts=4 sw=4 sts=4 tw=100 */
