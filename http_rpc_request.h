// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// Author: qinzuoyan01 (Qin Zuoyan)

#ifndef _TRIDENT_HTTP_RPC_REQUEST_H_
#define _TRIDENT_HTTP_RPC_REQUEST_H_

#include <map>

#include <trident/rapidjson/document.h>

#include <trident/rpc_request.h>

namespace trident {

class HTTPRpcRequestParser;

class HTTPRpcRequest;
typedef trident::shared_ptr<HTTPRpcRequest> HTTPRpcRequestPtr;

class HTTPResponse;

class HTTPRpcRequest : public RpcRequest
{
public:
    HTTPRpcRequest();
    virtual ~HTTPRpcRequest();

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
    enum RenderType
    {
        JSON = 1,
        PROTOBUF = 2,
        HTML = 3
    };

private:
    // Parse http path.
    // @return false if parse failed.
    bool ParsePath();

    void SendResponse(
            const RpcServerStreamWPtr& server_stream,
            const HTTPResponse& response);

    static bool RenderResponse(
            google::protobuf::io::ZeroCopyOutputStream* output,
            const RenderType type,
            const std::string& body);

    static bool RenderResponse(
            google::protobuf::io::ZeroCopyOutputStream* output,
            const HTTPResponse& response);

    static rapidjson::Document* ParseJson(
            const char* str,
            std::string& err);

    void InnerProcess(
            const RpcServerStreamWPtr& server_stream,
            const ServicePoolPtr& service_pool);

private:
    friend class HTTPRpcRequestParser;
    friend class WebService;

    enum Type
    {
        GET = 0,
        POST = 1,
        POST_PB = 2
    };
    Type                               _type;
    std::string                        _original_path;
    std::string                        _decoded_path;
    std::string                        _path;
    std::string                        _query_string;
    std::string                        _fragment_id;
    std::string                        _method;
    std::map<std::string, std::string> _query_params;
    std::string                        _http_version;
    std::map<std::string, std::string> _headers;
    ReadBufferPtr                      _req_body;
    rapidjson::Document*               _req_json;
}; // class HTTPRpcRequest

} // namespace trident

#endif // _TRIDENT_HTTP_RPC_REQUEST_H_

