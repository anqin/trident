// Copyright (c) 2014 Baidu.com, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

#ifndef _TRIDENT_RPC_CHANNEL_H_
#define _TRIDENT_RPC_CHANNEL_H_

#include <google/protobuf/service.h>

#include <trident/common.h>

namespace trident {


// Defined in other files.
class RpcClient;
class RpcChannelImpl;

struct RpcChannelOptions {
    // Connect timeout (in seconds).
    // If a request can't get an healthy connection after a connect_timeout
    // milliseconds, it will fail and return to the caller.
    //
    // Not supported now.
    int64 connect_timeout;

    RpcChannelOptions()
        : connect_timeout(10)
    {}
};

class RpcChannel : public google::protobuf::RpcChannel
{
public:
    // The "server_address" should be in format of "ip:port".
    RpcChannel(RpcClient* rpc_client,
               const std::string& server_address,
               const RpcChannelOptions& options = RpcChannelOptions());
    RpcChannel(RpcClient* rpc_client,
               const std::string& server_ip,
               uint32 server_port,
               const RpcChannelOptions& options = RpcChannelOptions());
    virtual ~RpcChannel();

    // Check the channel's address is valid.  If not valid, the following invoke
    // of "CallMethod()" will return RPC_ERROR_RESOLVE_ADDRESS.
    bool IsAddressValid();

    // Implements the google::protobuf::RpcChannel interface.  If the
    // "done" is NULL, it's a synchronous call, or it's asynchronous and
    // uses the callback to inform the completion (or failure). 
    virtual void CallMethod(const ::google::protobuf::MethodDescriptor* method,
                            ::google::protobuf::RpcController* controller,
                            const ::google::protobuf::Message* request,
                            ::google::protobuf::Message* response,
                            ::google::protobuf::Closure* done);

public:
    const trident::shared_ptr<RpcChannelImpl>& impl() const
    {
        return _impl;
    }

private:
    trident::shared_ptr<RpcChannelImpl> _impl;

    TRIDENT_DISALLOW_EVIL_CONSTRUCTORS(RpcChannel);
}; // class RpcChannel


} // namespace trident

#endif // _TRIDENT_RPC_CHANNEL_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
