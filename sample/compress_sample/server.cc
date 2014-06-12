/***************************************************************************
 *
 * Copyright (c) 2013 The Trident Authors. All Rights Reserved
 *
 * 
 * CreateTime: 2013-02-22
 *
 * Description:
 *
 **************************************************************************/

#include <signal.h>
#include <unistd.h>
#include <trident/pbrpc.h>
#include "trident/sample/compress_sample/echo_service.pb.h"

class EchoServerImpl : public trident::test::EchoServer
{
public:
    EchoServerImpl() {}
    virtual ~EchoServerImpl() {}

private:
    virtual void Echo(google::protobuf::RpcController* /*controller*/,
                      const trident::test::EchoRequest* request,
                      trident::test::EchoResponse* response,
                      google::protobuf::Closure* done)
    {
        SLOG(NOTICE, "Echo(): request message: %s", request->message().c_str());
        response->set_message("echo message: " + request->message());
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

    trident::test::EchoServer* echo_service = new EchoServerImpl();
    if (!rpc_server.RegisterService(echo_service)) {
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
