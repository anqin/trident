// Copyright (c) 2014 Baidu.com, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

#ifndef _TRIDENT_FUNC_TRACER_H_
#define _TRIDENT_FUNC_TRACER_H_

#include <boost/current_function.hpp>

#include <trident/common_internal.h>

namespace trident {

namespace internal {

class FuncTracer
{
public:
    FuncTracer(const char* file, size_t line, const char* func)
        : _file(file)
        , _line(line)
        , _func(func)
    {
#if defined( LOG )
        LOG(INFO) << _file << ": " << _line << ": >" << _func << "()";
#else
        SLOG(TRACE, "%s: %u: >%s()", _file, _line, _func);
#endif
    }

    ~FuncTracer()
    {
#if defined( LOG )
        LOG(INFO) << _file << ": " << _line << ": <" << _func << "()";
#else
        SLOG(TRACE, "%s: %u: <%s()", _file, _line, _func);
#endif
    }

private:
    const char* _file;
    size_t _line;
    const char* _func;
}; // class Tracer

} // namespace internal

} // namespace trident

#if defined( TRIDENT_ENABLE_FUNCTION_TRACE )
# define TRIDENT_FUNCTION_TRACE \
    ::trident::internal::FuncTracer __trident_function_tracer__( \
            __FILE__, __LINE__, BOOST_CURRENT_FUNCTION)
#else
# define TRIDENT_FUNCTION_TRACE
#endif // defined( TRIDENT_ENABLE_FUNCTION_TRACE )

#endif // _TRIDENT_FUNC_TRACER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
