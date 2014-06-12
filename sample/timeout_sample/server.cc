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

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <trident/pbrpc.h>
#include "trident/sample/timeout_sample/sleep_service.pb.h"

class SleepServerImpl : public trident::test::SleepServer
{
public:
    SleepServerImpl() {}
    virtual ~SleepServerImpl() {}

    virtual void SleepWithServiceTimeout(google::protobuf::RpcController* controller,
                                         const trident::test::SleepRequest* request,
                                         trident::test::SleepResponse* response,
                                         google::protobuf::Closure* done)
    {
        SLOG(NOTICE, "SleepWithServiceTimeout(): request sleep time: %d", request->sleep_time());
        Sleep(controller, request, response, done);
    }

    virtual void SleepWithMethodTimeout(google::protobuf::RpcController* controller,
                                        const trident::test::SleepRequest* request,
                                        trident::test::SleepResponse* response,
                                        google::protobuf::Closure* done)
    {
        SLOG(NOTICE, "SleepWithMethodTimeout(): request sleep time: %d", request->sleep_time());
        Sleep(controller, request, response, done);
    }


private:
    void Sleep(google::protobuf::RpcController* controller,
               const trident::test::SleepRequest* request,
               trident::test::SleepResponse* response,
               google::protobuf::Closure* done)
    {
        if (controller->IsCanceled())
            done->Run();
        sleep(request->sleep_time());
        char tmp[100];
        sprintf(tmp, "sleep succeed for %d seconds", request->sleep_time());
        response->set_message(tmp);
        done->Run();
    }
};

volatile bool g_quit = false;

static void SignalIntHandler(int /* sig */)
{
    g_quit = true;
}

int main(int /*argc*/, char** /*argv*/)
{
    TRIDENT_SET_LOG_LEVEL(NOTICE);

    // Define an rpc server.
    trident::RpcServerOptions options;
    trident::RpcServer rpc_server(options);

    // Start rpc server.
    if (!rpc_server.Start("0.0.0.0:12321")) {
        SLOG(ERROR, "start server failed");
        return EXIT_FAILURE;
    }

    trident::test::SleepServer* sleep_service = new SleepServerImpl();
    if (!rpc_server.RegisterService(sleep_service)) {
        SLOG(ERROR, "export service failed");
        return EXIT_FAILURE;
    }

    signal(SIGINT, SignalIntHandler);
    signal(SIGTERM, SignalIntHandler);

    while (!g_quit) {
        sleep(1);
    }

    return EXIT_SUCCESS;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
