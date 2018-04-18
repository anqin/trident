// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// Author: qinzuoyan01 (Qin Zuoyan)

#ifndef _TRIDENT_BINARY_RPC_REQUEST_H_
#define _TRIDENT_BINARY_RPC_REQUEST_H_

#include <trident/rpc_message_header.h>
#include <trident/rpc_meta.pb.h>
#include <trident/rpc_request.h>

namespace trident {

class BinaryRpcRequestParser;

class BinaryRpcRequest;
typedef trident::shared_ptr<BinaryRpcRequest> BinaryRpcRequestPtr;

class BinaryRpcRequest : public RpcRequest
{
public:
    BinaryRpcRequest();
    virtual ~BinaryRpcRequest();

    virtual RpcRequestType RequestType();

    virtual std::string Method();

    virtual uint64 SequenceId();

    virtual void ProcessRequest(
            const RpcServerStreamWPtr& server_stream,
            const ServicePoolPtr& service_pool);

    virtual ReadBufferPtr AssembleSucceedResponse(
            const RpcControllerImplPtr& cntl,
            const google::protobuf::Message* response,
            std::string& err);

    virtual ReadBufferPtr AssembleFailedResponse(
            int32 error_code,
            const std::string& reason,
            std::string& err);

private:
    friend class BinaryRpcRequestParser;

    RpcMessageHeader _req_header;
    RpcMeta          _req_meta;
    ReadBufferPtr    _req_body;
}; // class BinaryRpcRequest

} // namespace trident

#endif // _TRIDENT_BINARY_RPC_REQUEST_H_

