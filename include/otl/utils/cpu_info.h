//
// Created by kevin on 2022/8/19.
//

#ifndef OTL_CPU_INFO_H
#define OTL_CPU_INFO_H


#include "platform.h"
#include "api.h"
#if OTL_PLATFORM_OS_WINDOWS
#include <intrin.h>
#endif

namespace otl{

    enum CPUFeature {
        MMX = 0,
        SSE = 1,
        SSE2 = 2,
        SSE3 = 3,
        SSSE3 = 4,
        SSE4_1 = 5,
        SSE4_2 = 6,
        AVX = 12,
        AVX2 = 14,
        FMA = 15,
    };

    inline const char *cpu_feature_str(CPUFeature feature) {
        switch (feature) {
            case otl::MMX: return "MMX";
            case otl::SSE: return "SSE";
            case otl::SSE2: return "SSE2";
            case otl::SSE3: return "SSE3";
            case otl::SSSE3: return "SSSE3";
            case otl::SSE4_1: return "SSE4_1";
            case otl::SSE4_2: return "SSE4_2";
            case otl::AVX: return "AVX";
            case otl::AVX2: return "AVX2";
            case otl::FMA: return "FMA";
            default:break;
        }
        return "Unknown";
    }

    bool OTL_DEBUG_API check_cpu_feature(CPUFeature feature);

}

#endif //OTL_CPU_INFO_H
