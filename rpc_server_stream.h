// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// Author: qinzuoyan01 (Qin Zuoyan)

#ifndef _TRIDENT_RPC_SERVER_STREAM_H_
#define _TRIDENT_RPC_SERVER_STREAM_H_

#include <trident/rpc_error_code.h>
#include <trident/rpc_meta.pb.h>
#include <trident/rpc_server_message_stream.h>

namespace trident {

// Callback function when received request message.
typedef boost::function<void(
        const RpcServerStreamWPtr& /* stream */,
        const RpcRequestPtr& /* request */)> ReceivedRequestCallback;

/// Callback function when send response message done.
//  * if "status" == RPC_SUCCESS, means send response succeed;
//  * else, means send failed.
typedef boost::function<void(
        RpcErrorCode /* status */)> SendResponseCallback;

class RpcServerStream : public RpcServerMessageStream<SendResponseCallback>
{
public:
    RpcServerStream(IOService& io_service)
        : RpcServerMessageStream<SendResponseCallback>(
                ROLE_TYPE_SERVER, io_service, RpcEndpoint())
    {}

    virtual ~RpcServerStream()
    {
        TRIDENT_FUNCTION_TRACE;
        close("stream destructed");
    }

    // Set the callback function when received request.
    void set_received_request_callback(
            const ReceivedRequestCallback& callback)
    {
        _received_request_callback = callback;
    }

    // Get the callback function when received request.
    const ReceivedRequestCallback& received_request_callback() const
    {
        return _received_request_callback;
    }

    // Send response message.  No timeout is set for sending response.
    // If send done, on mater succeed or failed, SendResponseCallback will be called.
    // @param message  the response message to send, including the header.  not null.
    // @param callback  the callback function when send succeed or failed.  NULL means no callback.
    void send_response(const ReadBufferPtr& message,
            const SendResponseCallback& callback)
    {
        TRIDENT_FUNCTION_TRACE;

        async_send_message(message, callback);
    }

private:
    virtual void on_closed()
    {
        TRIDENT_FUNCTION_TRACE;

        // do nothing
    }

    virtual bool on_sending(
            const ReadBufferPtr& /* response_message */,
            const SendResponseCallback& /* callback */)
    {
        TRIDENT_FUNCTION_TRACE;

        return true;
    }

    virtual void on_sent(
            const ReadBufferPtr& /* response_message */,
            const SendResponseCallback& callback)
    {
        TRIDENT_FUNCTION_TRACE;

        if (callback) callback(RPC_SUCCESS);
    }

    virtual void on_send_failed(
            RpcErrorCode error_code,
            const ReadBufferPtr& /* response_message */,
            const SendResponseCallback& callback)
    {
        TRIDENT_FUNCTION_TRACE;

        if (callback) callback(error_code);
    }

    virtual void on_received(
            const RpcRequestPtr& request)
    {
        TRIDENT_FUNCTION_TRACE;

        if (_received_request_callback)
        {
            _received_request_callback(
                    trident::dynamic_pointer_cast<RpcServerStream>(shared_from_this()),
                    request);
        }
    }

private:
    ReceivedRequestCallback _received_request_callback;
}; // class RpcServerStream

} // namespace trident

#endif // _TRIDENT_RPC_SERVER_STREAM_H_

