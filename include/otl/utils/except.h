//
// Created by kevin on 2022/8/19.
//

#ifndef OTL_EXCEP_H
#define OTL_EXCEP_H


#include <exception>
#include <string>

#include "platform.h"

#if OTL_PLATFORM_CC_MSVC
#define OTL_NOEXCEPT
#else
#define OTL_NOEXCEPT noexcept
#endif

#include "api.h"

namespace otl {
    class OTL_DEBUG_API Exception : public std::exception {
    public:
    Exception();
    explicit Exception(const std::string &message);

    const char *what() const OTL_NOEXCEPT override;

    private:
    std::string m_message;
};

class OTL_DEBUG_API NullPointerException : public Exception {
public:
NullPointerException() : Exception() {}
explicit NullPointerException(const std::string &message) : Exception(message) {}
};
}


#endif //OTL_EXCEP_H
