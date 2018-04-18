// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// Author: Zuoyan Qin (qinzuoyan@gmail.com)

#include <trident/rpc_request.h>
#include <trident/binary_rpc_request_parser.h>
#include <trident/http_rpc_request_parser.h>

namespace trident {

void RpcRequestParser::RegisteredParsers(std::vector<RpcRequestParserPtr>* parsers)
{
    parsers->push_back(RpcRequestParserPtr(new BinaryRpcRequestParser()));
    parsers->push_back(RpcRequestParserPtr(new HTTPRpcRequestParser()));
}

} // namespace trident

