// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// 

#ifndef _TRIDENT_MOCK_TEST_HELPER_IMPL_H_
#define _TRIDENT_MOCK_TEST_HELPER_IMPL_H_

#include <map>

#include <trident/mock_test_helper.h>
#include <trident/locks.h>

namespace trident {


class MockTestHelperImpl : public MockTestHelper
{
public:
    MockTestHelperImpl() {}
    virtual ~MockTestHelperImpl() {}

    virtual void RegisterMockMethod(const std::string& method_name,
                                    MockMethodHookFunction* mock_method)
    {
        ScopedLocker<FastLock> _(_lock);
        _methods[method_name] = mock_method;
    }

    virtual void ClearMockMethod()
    {
        ScopedLocker<FastLock> _(_lock);
        _methods.clear();
    }

    virtual MockMethodHookFunction* GetMockMethod(const std::string& method_name) const
    {
        ScopedLocker<FastLock> _(_lock);
        std::map<std::string, MockMethodHookFunction*>::const_iterator it = _methods.find(method_name);
        return it == _methods.end() ? NULL : it->second;
    }

private:
    mutable FastLock _lock;
    std::map<std::string, MockMethodHookFunction*>  _methods;
};


} // namespace trident

#endif // _TRIDENT_MOCK_TEST_HELPER_IMPL_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
