//
// Created by kevin on 2022/8/19.
//

#include "utils/except.h"

namespace otl {
    Exception::Exception(const std::string &message)
            : m_message(message) {}

    const char *Exception::what() const OTL_NOEXCEPT {
    return m_message.c_str();
}

Exception::Exception()
        : m_message("Unknown exception.") {
}
}