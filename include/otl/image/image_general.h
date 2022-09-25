//
// Created by woshi on 2022/8/26.
//

#ifndef OTL_IMAGE_GENERAL_H
#define OTL_IMAGE_GENERAL_H
#include "common_struct.h"
#include "image.h"
#include "otl/utils/assert.h"
#include <cmath>
#include <algorithm>

namespace otl{
    using Polygon = otl::Polygon;
    using PointF = otl::PointF;

    bool static point_in_line(const Line& line, const PointF& point);

    bool static point_in_polygon(int32_t image_width, int32_t image_height, const Polygon& polygon, const PointF& point);
}
#endif //OTL_IMAGE_GENERAL_H
