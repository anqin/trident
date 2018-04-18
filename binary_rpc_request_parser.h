// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// Author: Zuoyan Qin (qinzuoyan@gmail.com)

#ifndef _TRIDENT_BINARY_RPC_REQUEST_PARSER_H_
#define _TRIDENT_BINARY_RPC_REQUEST_PARSER_H_

#include <trident/binary_rpc_request.h>
#include <trident/rpc_request_parser.h>

namespace trident {

class BinaryRpcRequestParser : public RpcRequestParser
{
public:
    BinaryRpcRequestParser();
    virtual ~BinaryRpcRequestParser();

    virtual const char* Name();

    virtual void Reset();

    virtual bool CheckMagicString(const char* magic_string);

    virtual int Parse(const char* buf, int data_size, int offset, int* bytes_consumed);

    virtual RpcRequestPtr GetRequest();

private:
    enum ParseState
    {
        PS_MAGIC_STRING,
        PS_MSG_HEADER,
        PS_MSG_BODY
    };
    ParseState _state; // current parsing state
    int _bytes_recved; // bytes received in current state
    BinaryRpcRequestPtr _req;
}; // class BinaryRpcRequestParser

} // namespace trident

#endif // _TRIDENT_BINARY_RPC_REQUEST_PARSER_H_

