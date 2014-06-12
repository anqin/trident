// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

#include <trident/rpc_client.h>
#include <trident/rpc_client_impl.h>

namespace trident {


RpcClient::RpcClient(const RpcClientOptions& options)
    : _impl(new RpcClientImpl(options))
{
    _impl->Start();
}

RpcClient::~RpcClient()
{
    Shutdown();
}

RpcClientOptions RpcClient::GetOptions()
{
    return _impl->GetOptions();
}

void RpcClient::ResetOptions(const RpcClientOptions& options)
{
    _impl->ResetOptions(options);
}

int RpcClient::ConnectionCount()
{
    return _impl->ConnectionCount();
}

void RpcClient::Shutdown()
{
    _impl->Stop();
}


} // namespace trident

/* vim: set ts=4 sw=4 sts=4 tw=100 */
