// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Author: Zuoyan Qin (qinzuoyan@gmail.com)

#include <trident/io_service.h>
#include <gtest/gtest.h>

namespace trident {

class EpollSupportTest: public ::testing::Test {};

#ifndef __APPLE__

TEST_F(EpollSupportTest, test)
{
    std::string output;
#if defined(BOOST_ASIO_HAS_IOCP)
    output = "iocp" ;
#elif defined(BOOST_ASIO_HAS_EPOLL)
    output = "epoll" ;
#elif defined(BOOST_ASIO_HAS_KQUEUE)
    output = "kqueue" ;
#elif defined(BOOST_ASIO_HAS_DEV_POLL)
    output = "/dev/poll" ;
#else
    output = "select" ;
#endif
    ASSERT_EQ("epoll", output);
}

#endif

} // end trident
