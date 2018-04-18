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
#include "echo_service.pb.h"

bool WebServlet(const trident::HTTPRequest& request, trident::HTTPResponse& response)
{
    SLOG(INFO, "WebServlet(): request message from %s:%u",
            request.client_ip.c_str(), request.client_port);
    SLOG(INFO, "HTTP-PATH=\"%s\"", request.path.c_str());
    std::map<std::string, std::string>::const_iterator it;
    const std::map<std::string, std::string>& query_params = *request.query_params;
    for (it = query_params.begin(); it != query_params.end(); ++it) {
        SLOG(INFO, "QueryParam[\"%s\"]=\"%s\"", it->first.c_str(), it->second.c_str());
    }
    const std::map<std::string, std::string>& headers = *request.headers;
    for (it = headers.begin(); it != headers.end(); ++it) {
        SLOG(INFO, "Header[\"%s\"]=\"%s\"", it->first.c_str(), it->second.c_str());
    }
    return response.content->Append("hello world!!!");
}

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
        trident::RpcController* cntl = static_cast<trident::RpcController*>(controller);
        SLOG(INFO, "Echo(): request message from %s: %s",
                cntl->RemoteAddress().c_str(), request->message().c_str());
        if (cntl->IsHttp()) {
            SLOG(INFO, "HTTP-PATH=\"%s\"", cntl->HttpPath().c_str());
            std::map<std::string, std::string>::const_iterator it;
            const std::map<std::string, std::string>& query_params = cntl->HttpQueryParams();
            for (it = query_params.begin(); it != query_params.end(); ++it) {
                SLOG(INFO, "QueryParam[\"%s\"]=\"%s\"", it->first.c_str(), it->second.c_str());
            }
            const std::map<std::string, std::string>& headers = cntl->HttpHeaders();
            for (it = headers.begin(); it != headers.end(); ++it) {
                SLOG(INFO, "Header[\"%s\"]=\"%s\"", it->first.c_str(), it->second.c_str());
            }
        }
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

    trident::Servlet servlet = trident::NewPermanentExtClosure(&WebServlet);
    rpc_server.RegisterWebServlet("/hello", servlet);

    // Start rpc server.
    if (!rpc_server.Start("0.0.0.0:8321")) {
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
