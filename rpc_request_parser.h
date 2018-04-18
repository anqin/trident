// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// Author: Zuoyan Qin (qinzuoyan@gmail.com)

#ifndef _TRIDENT_RPC_REQUEST_PARSER_H_
#define _TRIDENT_RPC_REQUEST_PARSER_H_

#include <trident/rpc_request.h>

#include <vector>

namespace trident {

class RpcRequestParser;
typedef trident::shared_ptr<RpcRequestParser> RpcRequestParserPtr;

class RpcRequestParser
{
public:
    RpcRequestParser() {}
    virtual ~RpcRequestParser(){}

    // Get the parser name.
    virtual const char* Name() = 0;

    // Reset the parser to init status.
    virtual void Reset() = 0;

    // Check if the parser identifies the magic string.
    virtual bool CheckMagicString(const char* magic_string) = 0;

    // Parse received data.
    //
    // @param buf  buffer start address (must be a tran buf)
    // @param data_size  data size
    // @param offset  the offset between real data and buffer start address
    // @param bytes_consumed  bytes used by this request
    //
    // @retval 1  request data ready
    // @retval 0  there are more bytes to be read
    // @retval -1  parse request fail
    virtual int Parse(const char* buf, int data_size, int offset, int* bytes_consumed) = 0;

    // Get the parsed request data.
    //
    // Preconditions:
    //   * Parse() returns 1
    virtual RpcRequestPtr GetRequest() = 0;

public:
    // Get all registered parsers.
    static void RegisteredParsers(std::vector<RpcRequestParserPtr>* parsers);
}; // class RpcRequestParser

} // namespace trident

#endif // _TRIDENT_RPC_REQUEST_PARSER_H_

