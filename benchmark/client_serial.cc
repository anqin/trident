// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Author: Zuoyan Qin (qinzuoyan@gmail.com)

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include "toft/base/random.h"
#include "toft/net/http/http_client.h"
#include "toft/system/threading/thread_pool.h"
#include <trident/pbrpc.h>
#include "echo_service.pb.h"

const int32_t g_thread_pool_min_size = 5;
const int32_t g_thread_pool_max_size = 20;
const int32_t g_thread_work_size = 5;

volatile bool g_quit = false;

enum Protocol {
    kHttp,
    kSofa,
};

static void SignalIntHandler(int /* sig */)
{
    g_quit = true;
}

const char * ProtocolStr(const Protocol& proto) {
    switch (proto) {
    case kHttp:
        return "kHttp";
    case kSofa:
        return "kSofa";
    default:
        return "unKnown";
    }
}

bool EmitHttpRequest(const std::string& address) {
    toft::HttpClient client;
    toft::HttpResponse response;
    toft::HttpClient::ErrorCode error;
    std::string uri = "http://" + address + "/echo";
    bool ret = client.Get(uri, &response, &error);
    if (false == ret) {
        SLOG(ERROR, "http request failed : %s", uri.c_str());
    }
    return ret;
}

bool EmitSofaRequest(trident::test::EchoServer_Stub* stub,
                     trident::RpcController* cntl,
                     trident::test::EchoRequest* request,
                     trident::test::EchoResponse* response) {
    stub->Echo(cntl, request, response, NULL);
    if (cntl->Failed()) {
        SLOG(ERROR, "sofa request failed: %s", cntl->ErrorText().c_str());
        return false;
    }
    if (response->message().size() != request->message().size()
            || response->message().at(0) != request->message().at(0)
            || response->message().at(response->message().size() / 2)
               != request->message().at(request->message().size() / 2)
            || response->message().at(response->message().size() - 1)
               != request->message().at(request->message().size() - 1)) {
        SLOG(ERROR, "response not matched");
        return false;
    }
    return true;
}

void SendRequest(const std::string* address,
                 const int32_t message_size,
                 const int32_t percentage) {
    std::string message_str;
    message_str.resize(message_size, 'z');

    TRIDENT_SET_LOG_LEVEL(NOTICE);

    // Define an rpc client.
    trident::RpcClientOptions client_options;
    trident::RpcClient rpc_client(client_options);

    // Define an rpc channel.
    trident::RpcChannelOptions channel_options;
    trident::RpcChannel rpc_channel(&rpc_client, *address, channel_options);

    // Prepare objects.
    trident::RpcController* cntl = new trident::RpcController();
    trident::test::EchoRequest* request = new trident::test::EchoRequest();
    request->set_message(message_str);
    trident::test::EchoResponse* response = new trident::test::EchoResponse();
    trident::test::EchoServer_Stub* stub = new trident::test::EchoServer_Stub(&rpc_channel);

    int count = 0;
    long elapsed_time_us;
    struct timeval tv1, tv2;
    struct timezone tz1, tz2;
    toft::Random random(1000);
    Protocol protocol;
    while (!g_quit) {
        ++count;
        cntl->Reset();
        cntl->SetTimeout(3000);
        gettimeofday(&tv1, &tz1);
        bool emit_status = false;
        if(random.Uniform(100) < percentage) {
            protocol = kHttp;
            emit_status = EmitHttpRequest(*address);
        } else {
            protocol = kSofa;
            emit_status = EmitSofaRequest(stub, cntl, request, response);
        }
        gettimeofday(&tv2, &tz2);
        elapsed_time_us = (tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec);
        SLOG(NOTICE, "Protocol: %s request succeed, elapsed time in us: %ld",
             ProtocolStr(protocol), elapsed_time_us);
    }

    delete request;
    delete response;
    delete cntl;
    delete stub;
    rpc_client.Shutdown();
}

int main(int argc, char** argv)
{
    // check command line arguments.
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <host> <port> <message_size> <percentage:opt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    signal(SIGINT, SignalIntHandler);
    signal(SIGTERM, SignalIntHandler);

    std::string address = argv[1] + std::string(":") + argv[2];
    int32_t message_size = atoi(argv[3]);
    int32_t percentage = 0;
    if (argc >= 4) {
        percentage = atoi(argv[4]);
    }
    toft::ThreadPool thread_pool(g_thread_pool_min_size, g_thread_pool_max_size);

    for (uint32_t i = 0; i < g_thread_work_size; ++i) {
        thread_pool.AddTask(toft::NewClosure(&SendRequest, &address,
                                             message_size, percentage));
    }

    return EXIT_SUCCESS;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
