//
// Created by woshi on 2022/8/19.
//

#ifndef OTL_STATIC_H
#define OTL_STATIC_H


#include <utility>
#include <functional>

#include "utils/except.h"

namespace otl {
    /**
     * StaticAction: for supporting static initialization
     */
    class StaticAction {
    public:
        template <typename FUNC, typename... Args>
        explicit StaticAction(FUNC func, Args&&... args) OTL_NOEXCEPT {
            std::bind(func, std::forward<Args>(args)...)();
        }
    };
}

#define _OTL_concat_name_core(x,y) (x##y)

#define _OTL_concat_name(x, y) _OTL_concat_name_core(x,y)

/**
 * generate an serial name by line
 */
#define OTL_serial_name(x) _OTL_concat_name(x, __LINE__)

/**
 * Static action
 */
#define OTL_STATIC_ACTION(func, ...) \
    namespace \
    { \
         otl::StaticAction OTL_serial_name(_OTL_static_action_)(func, ## __VA_ARGS__); \
    }


#endif //OTL_STATIC_H
