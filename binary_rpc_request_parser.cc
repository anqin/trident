// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// Author: Zuoyan Qin (qinzuoyan@gmail.com)

#include <trident/binary_rpc_request_parser.h>

namespace trident {

BinaryRpcRequestParser::BinaryRpcRequestParser() :
    _state(PS_MAGIC_STRING),
    _bytes_recved(0),
    _req(new BinaryRpcRequest())
{
}

BinaryRpcRequestParser::~BinaryRpcRequestParser()
{
}

const char* BinaryRpcRequestParser::Name()
{
    return "BinaryRpcRequestParser";
}

void BinaryRpcRequestParser::Reset()
{
    _state = PS_MAGIC_STRING;
    _bytes_recved = 0;
    _req.reset(new BinaryRpcRequest());
}

bool BinaryRpcRequestParser::CheckMagicString(const char* magic_string)
{
    SCHECK(_state == PS_MAGIC_STRING && _bytes_recved == 0);
    if (*reinterpret_cast<const uint32*>(magic_string) ==
            _req->_req_header.magic_str_value)
    {
        _state = PS_MSG_HEADER;
        _bytes_recved = 4;
        return true;
    }
    return false;
}

int BinaryRpcRequestParser::Parse(const char* buf,
        int data_size, int offset, int* bytes_consumed)
{
    if (data_size == 0)
    {
        return 0;
    }
    *bytes_consumed = 0;
    int bytes_remain, consume;
    switch (_state)
    {
        case PS_MSG_HEADER:
            bytes_remain = sizeof(RpcMessageHeader) - _bytes_recved;
            consume = std::min(data_size, bytes_remain);
            memcpy(reinterpret_cast<char*>(&_req->_req_header) + _bytes_recved,
                    buf + offset, consume);
            *bytes_consumed += consume;
            _bytes_recved += consume;
            if (_bytes_recved < static_cast<int>(sizeof(RpcMessageHeader)))
            {
                // header not complete
                return 0;
            }
            if (_req->_req_header.message_size == 0)
            {
                // all complete
                return 1;
            }
            // header complete
            data_size -= consume;
            offset += consume;
            _state = PS_MSG_BODY;
            _bytes_recved = 0; // because message_size not include the header
            if (data_size == 0)
            {
                return 0;
            }
        case PS_MSG_BODY:
            bytes_remain = _req->_req_header.message_size - _bytes_recved;
            consume = std::min(data_size, bytes_remain);
            _req->_req_body->Append(BufHandle(const_cast<char*>(buf), consume, offset));
            *bytes_consumed += consume;
            _bytes_recved += consume;
            if (_bytes_recved == _req->_req_header.message_size)
            {
                // receive body complete
                if (!_req->_req_meta.ParseFromBoundedZeroCopyStream(
                            _req->_req_body.get(), _req->_req_header.meta_size))
                {
                    // parse meta failed
#if 0
                    LOG(ERROR) << "Parse(): " << RpcEndpointToString(_req->_remote_endpoint)
                               << ": parse rpc meta failed";
#else
                    SLOG(ERROR, "Parse(): %s: parse rpc meta failed",
                            RpcEndpointToString(_req->_remote_endpoint).c_str());
#endif
                    return -1;
                }
                return 1;
            }
            return 0;
        default:
            SCHECK(false);
            return -1;
    }
}

RpcRequestPtr BinaryRpcRequestParser::GetRequest()
{
    return _req;
}

} // namespace trident

