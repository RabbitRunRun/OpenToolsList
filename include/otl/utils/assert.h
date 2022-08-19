//
// Created by kevin on 2022/8/19.
//

#ifndef OTL_ASSERT_H
#define OTL_ASSERT_H

#include "log.h"

#include <cfloat>

namespace otl {
    template <typename T>
    class __near_zero {
    public:
        using check_value = T;
        static bool check(check_value value) { return value == 0; }
    };

    template <>
    class __near_zero<double> {
    public:
        using check_value = double;
        static bool check(check_value value) {
            return (value > 0.0 ? value - 0.0 : 0.0 - value) < DBL_EPSILON;
        }
    };

    template <>
    class __near_zero<float> {
    public:
        using check_value = float;
        static bool check(check_value value) {
            return (value > 0.0f ? value - 0.0f : 0.0f - value) < FLT_EPSILON;
        }
    };

    template <typename T>
    inline bool near_zero(T value) {
        return __near_zero<T>::check(value);
    }
}

#define OTL_ASSERT(condition) OTL_LOG((condition) ? otl::LOG_NONE : otl::LOG_FATAL)("Assertion failed: (")(#condition)("). ")
#define OTL_CHECK(condition) OTL_LOG((condition) ? otl::LOG_NONE : otl::LOG_ERROR)("Check failed: (")(#condition)("). ")

#define OTL_CHECK_EQ(lhs, rhs) OTL_CHECK((lhs) == (rhs))
#define OTL_CHECK_NQ(lhs, rhs) OTL_CHECK((lhs) != (rhs))

#define OTL_CHECK_LE(lhs, rhs) OTL_CHECK((lhs) <= (rhs))
#define OTL_CHECK_GE(lhs, rhs) OTL_CHECK((lhs) >= (rhs))

#define OTL_CHECK_LT(lhs, rhs) OTL_CHECK((lhs) < (rhs))
#define OTL_CHECK_GT(lhs, rhs) OTL_CHECK((lhs) > (rhs))

#define OTL_AUTO_ASSERT(condition) (OTL_LOG((condition) ? otl::LOG_NONE : otl::LOG_FATAL)("Assertion failed: (")(#condition)(").") << otl::fatal)
#define OTL_AUTO_CHECK(condition) (OTL_LOG((condition) ? otl::LOG_NONE : otl::LOG_ERROR)("Check failed: (")(#condition)(").") << otl::eject)

#define OTL_AUTO_CHECK_EQ(lhs, rhs) OTL_AUTO_CHECK((lhs) == (rhs))
#define OTL_AUTO_CHECK_NQ(lhs, rhs) OTL_AUTO_CHECK((lhs) != (rhs))

#define OTL_AUTO_CHECK_LE(lhs, rhs) OTL_AUTO_CHECK((lhs) <= (rhs))
#define OTL_AUTO_CHECK_GE(lhs, rhs) OTL_AUTO_CHECK((lhs) >= (rhs))

#define OTL_AUTO_CHECK_LT(lhs, rhs) OTL_AUTO_CHECK((lhs) < (rhs))
#define OTL_AUTO_CHECK_GT(lhs, rhs) OTL_AUTO_CHECK((lhs) > (rhs))

#endif //OTL_ASSERT_H
