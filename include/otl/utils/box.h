//
// Created by kevin on 2022/8/19.
//

#ifndef OTL_BOX_H
#define OTL_BOX_H


#include <string>
#include <vector>
#include <utility>
#include <chrono>

#include "api.h"

namespace otl {
    using time_point = decltype(std::chrono::system_clock::now());

    /**
     * get edit distance of edit lhs to rhs
     * @param lhs original string
     * @param rhs wanted string
     * @return edit distance, 0 for `lhs == rhs`
     */
    OTL_DEBUG_API int edit_distance(const std::string &lhs, const std::string &rhs);

    /**
     * get `bins` bins split set [first, second)
     * @param first min number
     * @param second max number
     * @param bins number of bins
     * @return A list contains splited bins
     * @note Example input(0, 10, 3) returns [(0, 4), (4, 8), (8, 10)]
     */
    OTL_DEBUG_API std::vector<std::pair<int, int>> split_bins(int first, int second, int bins);

    /**
     * get `bins` bins split set [first, second)
     * @param first min number
     * @param second max number
     * @param bins number of bins
     * @return A list contains splited bins
     * @note Example input(0, 10, 3) returns [(0, 4), (4, 8), (8, 10)]
     */
    OTL_DEBUG_API std::vector<std::pair<size_t, size_t>> lsplit_bins(size_t first, size_t second, size_t bins);

    OTL_DEBUG_API std::string to_string(time_point tp, const std::string &format = "%Y-%m-%d %H:%M:%S");

    /**
     * return format now time string
     * @param format same as strftime
     * @return string contains now time
     * @see strftime
     */
    OTL_DEBUG_API std::string now_time(const std::string &format = "%Y-%m-%d %H:%M:%S");

    OTL_DEBUG_API std::vector<std::string> Split(const std::string &str, const std::string &sep, size_t _size = 1);

    OTL_DEBUG_API std::string Join(const std::vector<std::string>& list, const std::string &sep);

    OTL_DEBUG_API  std::string memory_size_string(uint64_t memory_size);
}


#endif //OTL_BOX_H
