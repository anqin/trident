// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

#include <sstream>

#include <trident/rpc_channel.h>
#include <trident/rpc_channel_impl.h>
#include <trident/rpc_client.h>

namespace trident {


RpcChannel::RpcChannel(RpcClient* rpc_client,
        const std::string& server_address,
        const RpcChannelOptions& options)
    : _impl(new RpcChannelImpl(rpc_client->impl(), server_address, options))
{
}

RpcChannel::RpcChannel(RpcClient* rpc_client,
        const std::string& server_ip,
        uint32 server_port,
        const RpcChannelOptions& options)
{
    std::ostringstream os;
    os << server_ip << ":" << server_port;
    _impl.reset(new RpcChannelImpl(rpc_client->impl(), os.str(), options));
}

RpcChannel::~RpcChannel()
{
}

bool RpcChannel::IsAddressValid()
{
    return _impl->IsAddressValid();
}

void RpcChannel::CallMethod(const ::google::protobuf::MethodDescriptor* method,
                            ::google::protobuf::RpcController* controller,
                            const ::google::protobuf::Message* request,
                            ::google::protobuf::Message* response,
                            ::google::protobuf::Closure* done)
{
    _impl->CallMethod(method, controller, request, response, done);
}


} // namespace trident

/* vim: set ts=4 sw=4 sts=4 tw=100 */
