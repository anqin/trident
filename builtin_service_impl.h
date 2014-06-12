// Copyright (c) 2014 Baidu.com, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

#ifndef _TRIDENT_BUILTIN_SERVICE_IMPL_H_
#define _TRIDENT_BUILTIN_SERVICE_IMPL_H_

#include <trident/common_internal.h>
#include <trident/builtin_service.pb.h>

namespace trident {

namespace builtin {

class BuiltinServiceImpl : public BuiltinService {
public:
    BuiltinServiceImpl(const RpcServerImplWPtr& rpc_server,
                       const ServicePoolWPtr& service_pool,
                       bool disable_list_service = false);
    virtual ~BuiltinServiceImpl();

    virtual void Health(::google::protobuf::RpcController* controller,
            const ::trident::builtin::HealthRequest* request,
            ::trident::builtin::HealthResponse* response,
            ::google::protobuf::Closure* done);

    virtual void ServerOptions(::google::protobuf::RpcController* controller,
            const ::trident::builtin::ServerOptionsRequest* request,
            ::trident::builtin::ServerOptionsResponse* response,
            ::google::protobuf::Closure* done);

    virtual void UpdateOptions(::google::protobuf::RpcController* controller,
            const ::trident::builtin::UpdateOptionsRequest* request,
            ::trident::builtin::UpdateOptionsResponse* response,
            ::google::protobuf::Closure* done);

    virtual void ServerStatus(::google::protobuf::RpcController* controller,
            const ::trident::builtin::ServerStatusRequest* request,
            ::trident::builtin::ServerStatusResponse* response,
            ::google::protobuf::Closure* done);

    virtual void ListService(::google::protobuf::RpcController* controller,
            const ::trident::builtin::ListServiceRequest* request,
            ::trident::builtin::ListServiceResponse* response,
            ::google::protobuf::Closure* done);

    virtual void Stat(::google::protobuf::RpcController* controller,
            const ::trident::builtin::StatRequest* request,
            ::trident::builtin::StatResponse* response,
            ::google::protobuf::Closure* done);

private:
    RpcServerImplWPtr _rpc_server;
    ServicePoolWPtr _service_pool;
    bool _disable_list_service;

    MutexLock _list_service_lock;
    ListServiceResponse _list_service_last_response;
    int _list_service_last_count;
};

} // namespace builtin

} // namespace trident

#endif // _TRIDENT_BUILTIN_SERVICE_IMPL_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
