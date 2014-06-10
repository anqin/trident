// Copyright (c) 2014 Baidu.com, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Author: qinzuoyan01@baidu.com (Qin Zuoyan)

#ifndef _SOFA_PBRPC_COMMON_INTERNAL_H_
#define _SOFA_PBRPC_COMMON_INTERNAL_H_

#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <trident/common.h>
#include <trident/atomic.h>
#include <trident/counter.h>
#include <trident/func_tracer.h>
#include <trident/io_service.h>
#include <trident/locks.h>
#include <trident/ptime.h>

namespace trident {
namespace pbrpc {

class RpcControllerImpl;
typedef trident::pbrpc::shared_ptr<RpcControllerImpl> RpcControllerImplPtr;
typedef trident::pbrpc::weak_ptr<RpcControllerImpl> RpcControllerImplWPtr;

class RpcChannelImpl;
typedef trident::pbrpc::shared_ptr<RpcChannelImpl> RpcChannelImplPtr;

class RpcClientImpl;
typedef trident::pbrpc::shared_ptr<RpcClientImpl> RpcClientImplPtr;

class RpcServerImpl;
typedef trident::pbrpc::shared_ptr<RpcServerImpl> RpcServerImplPtr;
typedef trident::pbrpc::weak_ptr<RpcServerImpl> RpcServerImplWPtr;

class RpcClientStream;
typedef trident::pbrpc::shared_ptr<RpcClientStream> RpcClientStreamPtr;
typedef trident::pbrpc::weak_ptr<RpcClientStream> RpcClientStreamWPtr;

class RpcServerStream;
typedef trident::pbrpc::shared_ptr<RpcServerStream> RpcServerStreamPtr;
typedef trident::pbrpc::weak_ptr<RpcServerStream> RpcServerStreamWPtr;

class RpcListener;
typedef trident::pbrpc::shared_ptr<RpcListener> RpcListenerPtr;

class TimerWorker;
typedef trident::pbrpc::shared_ptr<TimerWorker> TimerWorkerPtr;

class RpcTimeoutManager;
typedef trident::pbrpc::shared_ptr<RpcTimeoutManager> RpcTimeoutManagerPtr;

class ThreadGroup;
typedef trident::pbrpc::shared_ptr<ThreadGroup> ThreadGroupPtr;

class ServicePool;
typedef trident::pbrpc::shared_ptr<ServicePool> ServicePoolPtr;
typedef trident::pbrpc::weak_ptr<ServicePool> ServicePoolWPtr;

class FlowController;
typedef trident::pbrpc::shared_ptr<FlowController> FlowControllerPtr;

class WaitEvent;
typedef trident::pbrpc::shared_ptr<WaitEvent> WaitEventPtr;

#define SOFA_PBRPC_DECLARE_RESOURCE_COUNTER(name_) \
    extern trident::pbrpc::AtomicCounter g_trident_counter_##name_
#define SOFA_PBRPC_DEFINE_RESOURCE_COUNTER(name_) \
    trident::pbrpc::AtomicCounter g_trident_counter_##name_(0)
#define SOFA_PBRPC_INC_RESOURCE_COUNTER(name_) \
    ++g_trident_counter_##name_
#define SOFA_PBRPC_DEC_RESOURCE_COUNTER(name_) \
    --g_trident_counter_##name_
#define SOFA_PBRPC_GET_RESOURCE_COUNTER(name_) \
    static_cast<int>(g_trident_counter_##name_)

SOFA_PBRPC_DECLARE_RESOURCE_COUNTER(RpcByteStream);
SOFA_PBRPC_DECLARE_RESOURCE_COUNTER(RpcListener);

} // namespace pbrpc
} // namespace trident

#endif // _SOFA_PBRPC_COMMON_INTERNAL_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
