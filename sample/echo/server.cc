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

#include <signal.h>
#include <unistd.h>
#include <trident/pbrpc.h>
#include "echo_service.pb.h"

class EchoServerImpl : public trident::test::EchoServer
{
public:
    EchoServerImpl() {}
    virtual ~EchoServerImpl() {}

private:
    virtual void Echo(google::protobuf::RpcController* controller,
                      const trident::test::EchoRequest* request,
                      trident::test::EchoResponse* response,
                      google::protobuf::Closure* done)
    {
        SLOG(NOTICE, "Echo(): request message from %s: %s",
                static_cast<trident::RpcController*>(controller)->RemoteAddress().c_str(),
                request->message().c_str());
        response->set_message("echo message: " + request->message());
        done->Run();
    }
};

bool thread_init_func()
{
    sleep(1);
    SLOG(INFO, "Init work thread succeed");
    return true;
}

void thread_dest_func()
{
    SLOG(INFO, "Destroy work thread succeed");
}

int main()
{
    TRIDENT_SET_LOG_LEVEL(NOTICE);

    // Define an rpc server.
    trident::RpcServerOptions options;
    options.work_thread_init_func = trident::NewPermanentExtClosure(&thread_init_func);
    options.work_thread_dest_func = trident::NewPermanentExtClosure(&thread_dest_func);
    trident::RpcServer rpc_server(options);

    // Start rpc server.
    if (!rpc_server.Start("0.0.0.0:12321")) {
        SLOG(ERROR, "start server failed");
        return EXIT_FAILURE;
    }
    
    // Register service.
    trident::test::EchoServer* echo_service = new EchoServerImpl();
    if (!rpc_server.RegisterService(echo_service)) {
        SLOG(ERROR, "export service failed");
        return EXIT_FAILURE;
    }

    // Wait signal.
    rpc_server.Run();

    // Stop rpc server.
    rpc_server.Stop();

    // Delete closures.
    // Attention: should delete the closures after server stopped, or may be crash.
    delete options.work_thread_init_func;
    delete options.work_thread_dest_func;

    return EXIT_SUCCESS;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
