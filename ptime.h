// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

#ifndef _TRIDENT_PTIME_H_
#define _TRIDENT_PTIME_H_

#include <cstdio> // for snprintf()

#include <boost/date_time/posix_time/posix_time.hpp>

namespace trident {


typedef boost::posix_time::ptime PTime;
typedef boost::posix_time::time_duration TimeDuration;

inline PTime ptime_now()
{
    return boost::posix_time::microsec_clock::universal_time();
}

inline PTime ptime_infin()
{
    return boost::posix_time::ptime(boost::posix_time::pos_infin);
}

inline std::string ptime_to_string(const PTime& t)
{
    PTime::date_type date = t.date();
    TimeDuration tod = t.time_of_day();
    char buf[100];
    snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d.%06ld", 
            (int)date.year(),
            (int)date.month(),
            (int)date.day(),
            tod.hours(),
            tod.minutes(),
            tod.seconds(),
            tod.fractional_seconds());
    return buf;
}

inline TimeDuration time_duration_hours(int64_t n)
{
    return boost::posix_time::hours(static_cast<long>(n));
}

inline TimeDuration time_duration_minutes(int64_t n)
{
    return boost::posix_time::minutes(static_cast<long>(n));
}

inline TimeDuration time_duration_seconds(int64_t n)
{
    return boost::posix_time::seconds(static_cast<long>(n));
}

inline TimeDuration time_duration_milliseconds(int64_t n)
{
    return boost::posix_time::milliseconds(static_cast<long>(n));
}

inline TimeDuration time_duration_microseconds(int64_t n)
{
    return boost::posix_time::microseconds(static_cast<long>(n));
}


} // namespace trident

#endif // _TRIDENT_PTIME_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
