//
// Created by kevin on 2022/8/19.
//

#include "otl/utils/log.h"
#include "utils/static.h"

#include <atomic>

namespace otl {
    static std::atomic<LogLevel> InnerGlobalLogLevel;

    LogLevel GlobalLogLevel(LogLevel level) {
        LogLevel pre_level = InnerGlobalLogLevel;
        InnerGlobalLogLevel = level;
        return pre_level;
    }

    LogLevel GlobalLogLevel() {
        return InnerGlobalLogLevel;
    }
}

OTL_STATIC_ACTION((otl::LogLevel(*)(otl::LogLevel))otl::GlobalLogLevel, otl::LOG_INFO)
