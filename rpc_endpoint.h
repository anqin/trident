// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

#ifndef _TRIDENT_RPC_ENDPOINT_H_
#define _TRIDENT_RPC_ENDPOINT_H_

#include <trident/common_internal.h>

namespace trident {


typedef boost::asio::ip::tcp::endpoint RpcEndpoint;

std::string RpcEndpointToString(const RpcEndpoint& endpoint);

bool ResolveAddress(IOService& io_service,
        const std::string& host, const std::string& svc,
        RpcEndpoint* endpoint);

bool ResolveAddress(IOService& io_service,
        const std::string& address,
        RpcEndpoint* endpoint);


} // namespace trident

#endif // _TRIDENT_RPC_ENDPOINT_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
