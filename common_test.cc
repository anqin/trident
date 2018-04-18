// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Author: Zuoyan Qin (qinzuoyan@gmail.com)

#include <trident/common.h>
#include <gtest/gtest.h>

namespace trident {

class CommonTest : public ::testing::Test
{
protected:
    CommonTest(){};
    virtual ~CommonTest(){};
    virtual void SetUp() {
        //Called befor every TEST_F(CommonTest, *)
    };
    virtual void TearDown() {
        //Called after every TEST_F(CommonTest, *)
    };
};

TEST_F(CommonTest, test_log)
{
    trident::internal::set_log_level(trident::LOG_LEVEL_NOTICE);
    int flag_notice = 0;
    SLOG(NOTICE, "notice message: %d: %s", ++flag_notice, "should be logged");
    ASSERT_EQ(1, flag_notice);
    int flag_trace = 0;
    SLOG(TRACE, "trace message: %d: %s", ++flag_trace, "should not be logged");
    ASSERT_EQ(0, flag_trace);
}

TEST_F(CommonTest, test_check)
{
    int value = 1;
    SCHECK_EQ(1, value);
    SCHECK_LE(1, value);
    SCHECK_LE(0, value);
    SCHECK_LT(0, value);
    SCHECK_GE(1, value);
    SCHECK_GE(2, value);
    SCHECK_GT(2, value);
}

static std::string s_test_log_buf;
void test_log_handler(
    trident::LogLevel level, const char* filename, int,
    const char *fmt, va_list ap)
{
    char buf[1024];
    vsnprintf(buf, 1024, fmt, ap);
    char result[1500];
    snprintf(result, 1024, "level=%d filename=%s %s", level, filename, buf);
    s_test_log_buf.assign(result);
}

} // end trident
