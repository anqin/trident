// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

#ifndef _TRIDENT_RPC_CHANNEL_IMPL_H_
#define _TRIDENT_RPC_CHANNEL_IMPL_H_

#include <trident/common_internal.h>
#include <trident/rpc_channel.h>
#include <trident/rpc_client_impl.h>
#include <trident/rpc_controller_impl.h>
#include <trident/rpc_endpoint.h>

namespace trident {


class RpcChannelImpl : public trident::enable_shared_from_this<RpcChannelImpl>
{
public:
    RpcChannelImpl(const RpcClientImplPtr& rpc_client_impl,
                   const std::string& server_address,
                   const RpcChannelOptions& options);

    virtual ~RpcChannelImpl();

    bool IsAddressValid();

    void CallMethod(const ::google::protobuf::MethodDescriptor* method,
                    ::google::protobuf::RpcController* controller,
                    const ::google::protobuf::Message* request,
                    ::google::protobuf::Message* response,
                    ::google::protobuf::Closure* done);

private:
    static void WaitDone(const RpcControllerImplPtr& cntl);

    void DoneCallback(google::protobuf::Closure* done,
                      const RpcControllerImplPtr& cntl);

    static void MockDoneCallback(RpcControllerImplPtr cntl,
            const ::google::protobuf::Message* request,
            ::google::protobuf::Message* response);

private:
    RpcClientImplPtr _client_impl;
    std::string _server_address;
    RpcChannelOptions _options;

    bool _is_mock;
    bool _resolve_address_succeed;
    RpcEndpoint _remote_endpoint;

    TRIDENT_DISALLOW_EVIL_CONSTRUCTORS(RpcChannelImpl);
}; // class RpcChannelImpl


} // namespace trident

#endif // _TRIDENT_RPC_CHANNEL_IMPL_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
