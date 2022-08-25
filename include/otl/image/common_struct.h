//
// Created by kevin on 2022/8/25.
//

#ifndef OTL_COMMON_STRUCT_H
#define OTL_COMMON_STRUCT_H
#include <memory>
namespace otl{
    struct PointF{
        float x;
        float y;
    };

    struct Rect{
        PointF top_left;
        PointF bottom_right;
    };

    struct Line{
        PointF p1;
        PointF p2;
    };

    struct Polygon{
        using shared_points =  std::shared_ptr<PointF>;
        Polygon(){}
        Polygon(size_t num){
            set_num(num);
        }
        void set_num(size_t num){
            size = num;
            points.reset(new PointF[size]);
        }

        size_t get_num() const {
            return size;
        }
        shared_points get_points(){
            return points;
        }
        shared_points points;
        size_t  size;
    };
}

#endif //OTL_COMMON_STRUCT_H
