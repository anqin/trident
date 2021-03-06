// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

#ifndef _TRIDENT_RPC_LISTENER_H_
#define _TRIDENT_RPC_LISTENER_H_

#include <trident/common_internal.h>
#include <trident/rpc_endpoint.h>
#include <trident/rpc_error_code.h>
#include <trident/locks.h>

namespace trident {


using boost::asio::ip::tcp;

class RpcListener : public trident::enable_shared_from_this<RpcListener>
{
    // Callback function when created or accepted a new connection.
    typedef boost::function<void(const RpcServerStreamPtr& /* stream */)> Callback;
    typedef boost::function<void(RpcErrorCode /* error_code */,
            const std::string& /* error_text */)> FailCallback;

public:
    static const int LISTEN_MAX_CONNECTIONS = 4096;
    
public:
    RpcListener(IOService& io_service, const RpcEndpoint& endpoint)
        : _io_service(io_service)
        , _endpoint(endpoint)
        , _endpoint_str(RpcEndpointToString(endpoint))
        , _acceptor(io_service)
        , _is_closed(false)
    {
        TRIDENT_INC_RESOURCE_COUNTER(RpcListener);
    }

    virtual ~RpcListener()
    {
        TRIDENT_FUNCTION_TRACE;
        close();
        TRIDENT_DEC_RESOURCE_COUNTER(RpcListener);
    }

    void close()
    {
        ScopedLocker<MutexLock> _(_close_lock);
        if (_is_closed) return;
        _is_closed = true;

        boost::system::error_code ec;
        _acceptor.cancel(ec);
        _acceptor.close(ec);

#if 0
        LOG(INFO) << "close(): listener closed: " << _endpoint_str;
#else
        SLOG(INFO, "close(): listener closed: %s", _endpoint_str.c_str());
#endif
    }

    bool is_closed()
    {
        ScopedLocker<MutexLock> _(_close_lock);
        return _is_closed;
    }

    // Set the callback funtion when created a new connection.
    template <typename T>
    void set_create_callback(const T& create_callback)
    {
        _create_callback = create_callback;
    }

    // Set the callback funtion when accepted a new connection.
    template <typename T>
    void set_accept_callback(const T& accept_callback)
    {
        _accept_callback = accept_callback;
    }

    // Set the callback funtion when failed to accept connection.
    template <typename T>
    void set_accept_fail_callback(const T& accept_fail_callback)
    {
        _accept_fail_callback = accept_fail_callback;
    }

    // Start listen.  Return false if failed.
    bool start_listen()
    {
        boost::system::error_code ec;

        _acceptor.open(_endpoint.protocol(), ec);
        if (ec)
        {
#if 0
            LOG(ERROR) << "start_listen(): open acceptor failed: "
                       << _endpoint_str << ": " << ec.message();
#else
            SLOG(ERROR, "start_listen(): open acceptor failed: %s: %s",
                    _endpoint_str.c_str(), ec.message().c_str());
#endif
            return false;
        }

        _acceptor.set_option(tcp::acceptor::reuse_address(true), ec);
        if (ec)
        {
#if 0
            LOG(ERROR) << "start_listen(): set acceptor option failed: "
                       << _endpoint_str << ": " << ec.message();
#else
            SLOG(ERROR, "start_listen(): set acceptor option failed: %s: %s",
                    _endpoint_str.c_str(), ec.message().c_str());
#endif
            return false;
        }

        _acceptor.bind(_endpoint, ec);
        if (ec)
        {
#if 0
            LOG(ERROR) << "start_listen(): bind acceptor failed: "
                       << _endpoint_str << ": " << ec.message();
#else
            SLOG(ERROR, "start_listen(): bind acceptor failed: %s: %s",
                    _endpoint_str.c_str(), ec.message().c_str());
#endif
            return false;
        }

        //_acceptor.listen(boost::asio::socket_base::max_connections, ec);
        _acceptor.listen(LISTEN_MAX_CONNECTIONS, ec);
        if (ec)
        {
#if 0
            LOG(ERROR) << "start_listen(): listen acceptor failed: "
                       << _endpoint_str << ": " << ec.message();
#else
            SLOG(ERROR, "start_listen(): listen acceptor failed: %s: %s",
                    _endpoint_str.c_str(), ec.message().c_str());
#endif
            return false;
        }

#if 0
        LOG(INFO) << "start_listen(): listen succeed: " << _endpoint_str;
#else
        SLOG(INFO, "start_listen(): listen succeed: %s", _endpoint_str.c_str());
#endif

        async_accept();

        return true;
    }

private:
    void async_accept()
    {
        RpcServerStreamPtr stream(new RpcServerStream(_io_service));

        if (_create_callback)
            _create_callback(stream);

        _acceptor.async_accept(stream->socket(), boost::bind(
                    &RpcListener::on_accept, shared_from_this(), stream, _1));
    }

    void on_accept(const RpcServerStreamPtr& stream,
            const boost::system::error_code& ec)
    {
        if (_is_closed)
            return;

        if (ec)
        {
#if 0
            LOG(ERROR) << "on_accept(): accept error at "
                       << _endpoint_str << ": " << ec.message();
#else
            SLOG(ERROR, "on_accept(): accept error at %s: %s",
                    _endpoint_str.c_str(), ec.message().c_str());
#endif

            close();

            if (_accept_fail_callback)
            {
                RpcErrorCode error_code = ec == boost::asio::error::no_descriptors ?
                    RPC_ERROR_TOO_MANY_OPEN_FILES : RPC_ERROR_UNKNOWN;
                _accept_fail_callback(error_code, ec.message());
            }
        }
        else
        {
            if (_accept_callback)
                _accept_callback(stream);

            stream->set_socket_connected();

#if 0
            LOG(INFO) << "on_accept(): accept connection at "
                      << _endpoint_str << ": " << RpcEndpointToString(stream->remote_endpoint());
#else
            SLOG(INFO, "on_accept(): accept connection at %s: %s",
                    _endpoint_str.c_str(), RpcEndpointToString(stream->remote_endpoint()).c_str());
#endif

            async_accept();
        }
    }

private:
    IOService& _io_service;
    RpcEndpoint _endpoint;
    std::string _endpoint_str;
    Callback _create_callback;
    Callback _accept_callback;
    FailCallback _accept_fail_callback;
    tcp::acceptor _acceptor;
    volatile bool _is_closed;
    MutexLock _close_lock;

    TRIDENT_DISALLOW_EVIL_CONSTRUCTORS(RpcListener);
}; // class RpcListener


} // namespace trident

#endif // _TRIDENT_RPC_LISTENER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
