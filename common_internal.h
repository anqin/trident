// Copyright (c) 2014 Baidu.com, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

#ifndef _TRIDENT_COMMON_INTERNAL_H_
#define _TRIDENT_COMMON_INTERNAL_H_

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


class RpcControllerImpl;
typedef trident::shared_ptr<RpcControllerImpl> RpcControllerImplPtr;
typedef trident::weak_ptr<RpcControllerImpl> RpcControllerImplWPtr;

class RpcChannelImpl;
typedef trident::shared_ptr<RpcChannelImpl> RpcChannelImplPtr;

class RpcClientImpl;
typedef trident::shared_ptr<RpcClientImpl> RpcClientImplPtr;

class RpcServerImpl;
typedef trident::shared_ptr<RpcServerImpl> RpcServerImplPtr;
typedef trident::weak_ptr<RpcServerImpl> RpcServerImplWPtr;

class RpcClientStream;
typedef trident::shared_ptr<RpcClientStream> RpcClientStreamPtr;
typedef trident::weak_ptr<RpcClientStream> RpcClientStreamWPtr;

class RpcServerStream;
typedef trident::shared_ptr<RpcServerStream> RpcServerStreamPtr;
typedef trident::weak_ptr<RpcServerStream> RpcServerStreamWPtr;

class RpcListener;
typedef trident::shared_ptr<RpcListener> RpcListenerPtr;

class TimerWorker;
typedef trident::shared_ptr<TimerWorker> TimerWorkerPtr;

class RpcTimeoutManager;
typedef trident::shared_ptr<RpcTimeoutManager> RpcTimeoutManagerPtr;

class ThreadGroup;
typedef trident::shared_ptr<ThreadGroup> ThreadGroupPtr;

class ServicePool;
typedef trident::shared_ptr<ServicePool> ServicePoolPtr;
typedef trident::weak_ptr<ServicePool> ServicePoolWPtr;

class FlowController;
typedef trident::shared_ptr<FlowController> FlowControllerPtr;

class WaitEvent;
typedef trident::shared_ptr<WaitEvent> WaitEventPtr;

#define TRIDENT_DECLARE_RESOURCE_COUNTER(name_) \
    extern trident::AtomicCounter g_trident_counter_##name_
#define TRIDENT_DEFINE_RESOURCE_COUNTER(name_) \
    trident::AtomicCounter g_trident_counter_##name_(0)
#define TRIDENT_INC_RESOURCE_COUNTER(name_) \
    ++g_trident_counter_##name_
#define TRIDENT_DEC_RESOURCE_COUNTER(name_) \
    --g_trident_counter_##name_
#define TRIDENT_GET_RESOURCE_COUNTER(name_) \
    static_cast<int>(g_trident_counter_##name_)

TRIDENT_DECLARE_RESOURCE_COUNTER(RpcByteStream);
TRIDENT_DECLARE_RESOURCE_COUNTER(RpcListener);


} // namespace trident

#endif // _TRIDENT_COMMON_INTERNAL_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
