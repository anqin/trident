/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 *
 * 
 * CreateTime: 2013-02-22
 * 
 * Description: 
 * 
 **************************************************************************/

#include <unistd.h>
#include <trident/pbrpc.h>
#include "echo_service.pb.h"

void EchoCallback(trident::RpcController* cntl,
        trident::test::EchoRequest* request,
        trident::test::EchoResponse* response,
        bool* callbacked)
{
    SLOG(NOTICE, "RemoteAddress=%s", cntl->RemoteAddress().c_str());
    SLOG(NOTICE, "IsRequestSent=%s", cntl->IsRequestSent() ? "true" : "false");
    if (cntl->IsRequestSent())
    {
        SLOG(NOTICE, "LocalAddress=%s", cntl->LocalAddress().c_str());
        SLOG(NOTICE, "SentBytes=%ld", cntl->SentBytes());
    }

    if (cntl->Failed()) {
        SLOG(ERROR, "request failed: %s", cntl->ErrorText().c_str());
    }
    else {
        SLOG(NOTICE, "request succeed: %s", response->message().c_str());
    }

    delete cntl;
    delete request;
    delete response;
    *callbacked = true;
}

int main()
{
    TRIDENT_SET_LOG_LEVEL(NOTICE);

    // Define an rpc server.
    trident::RpcClientOptions client_options;
    trident::RpcClient rpc_client(client_options);

    // Define an rpc channel.
    trident::RpcChannelOptions channel_options;
    trident::RpcChannel rpc_channel(&rpc_client, "127.0.0.1:12321", channel_options);

    // Prepare parameters.
    trident::RpcController* cntl = new trident::RpcController();
    cntl->SetTimeout(3000);
    trident::test::EchoRequest* request = new trident::test::EchoRequest();
    request->set_message("Hello from qinzuoyan01");
    trident::test::EchoResponse* response = new trident::test::EchoResponse();
    bool callbacked = false;
    google::protobuf::Closure* done = trident::NewClosure(
            &EchoCallback, cntl, request, response, &callbacked);

    // Async call.
    trident::test::EchoServer_Stub stub(&rpc_channel);
    stub.Echo(cntl, request, response, done);

    // Wait call done.
    while (!callbacked) {
        usleep(100000);
    }

    return EXIT_SUCCESS;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
