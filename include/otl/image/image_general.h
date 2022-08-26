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

    template<typename T1, typename T2>
    static bool is_same(T1 a, T2 b){
        return std::abs(a - b) < FLT_EPSILON;
    }

    bool static point_in_image(int32_t image_width, int32_t image_height, const PointF& point){
        return (point.x >=0) && (point.x < image_width) && (point.y >= 0) && (point.y < image_height);
    }

    bool static point_in_line(const Line& line, const PointF& point){
        auto& p1 = line.p1;
        auto& p2 = line.p2;
        bool result = ((point.x - p1.x) * (p2.y - p1.y)) == ((point.y - p1.y) * (p2.x - p1.x));
        float x_min = std::min(p1.x, p2.x);
        float x_max = std::max(p1.x, p2.x);
        float y_min = std::min(p1.y, p2.y);
        float y_max = std::max(p1.y, p2.y);
        result = result && ((point.x >= x_min) && (point.x <= x_max) && (point.y >= y_min) && (point.y <= y_max));
        return result;
    }

    bool static point_in_polygon(int32_t image_width, int32_t image_height, const Polygon& polygon, const PointF& point){
        int points_num = (int)polygon.get_size();
        for (int i = 0; i < points_num; i++){
            OTL_ASSERT(point_in_image(image_width, image_height, polygon.point(i)));
        }
        bool in_poly = false;
        for (int i = 0; i < points_num; i++){
            PointF p1 = polygon.point(i);
            PointF p2 = polygon.point((i + 1) % points_num);//line

            int32_t line_min_y = (int32_t)std::min(p1.y,p2.y);
            int32_t line_max_y = (int32_t)std::max(p1.y, p2.y);
            if((point.y <= line_min_y) || (point.y > line_max_y)) continue;//no cross point or cross upper point or cross a horizontal line

            if(point_in_line(Line(p1, p2), point)) return true;// if point in line

            if(p1.y == p2.y) continue; //make sure y1 != y2

            int cross_point_x = int(p2.x - (p2.y - point.y) * (p2.x - p1.x) / (p2.y - p1.y));
            if(cross_point_x < point.x) continue; // no cross for ray line to right

            in_poly = !in_poly;
        }
        return in_poly;
    }
}
#endif //OTL_IMAGE_GENERAL_H
