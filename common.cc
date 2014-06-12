// Copyright (c) 2014 Baidu.com, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

#include <cstdio>
#include <cstdarg>
#include <cstdlib>

#include <trident/common.h>
#include <trident/ptime.h>

namespace trident {

namespace internal {

static LogLevel s_log_level = ::trident::LOG_LEVEL_ERROR;

LogLevel get_log_level()
{
    return s_log_level;
}

void set_log_level(LogLevel level)
{
    s_log_level = level;
}

void log_handler(LogLevel level, const char* filename, int line, const char *fmt, ...)
{
    static const char* level_names[] = { "FATAL", "ERROR", "WARNNING",
                                         "INFO", "TRACE", "DEBUG" };
    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, 1024, fmt, ap);
    va_end(ap);
#if 0
    fprintf(stderr, "libtrident_pbrpc %s %s %s:%d] %s\n",
            level_names[level],
            boost::posix_time::to_simple_string(
                boost::posix_time::microsec_clock::local_time()).c_str(),
            filename, line, buf);
#endif
    fprintf(stderr, "libtrident_pbrpc %s %s:%d] %s\n",
            level_names[level],
            filename, line, buf);
    fflush(stderr);

    if (level == ::trident::LOG_LEVEL_FATAL)
    {
        abort();
    }
}

} // namespace internal

} // namespace trident

/* vim: set ts=4 sw=4 sts=4 tw=100 */
