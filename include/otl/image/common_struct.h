//
// Created by kevin on 2022/8/25.
//

#ifndef OTL_COMMON_STRUCT_H
#define OTL_COMMON_STRUCT_H
#include <memory>
#include <vector>
namespace otl{
    struct PointF{
        float x;
        float y;
    };

    struct Rect{

        Rect(){}

        Rect(PointF p1, PointF p2){
            top_left = p1;
            bottom_right = p2;
        }

        PointF top_left;
        PointF bottom_right;
    };

    struct Line{

        Line(){}

        Line(PointF _p1, PointF _p2){
            p1 = _p1;
            p2 = _p2;
        }

        PointF p1;
        PointF p2;
    };

    struct Polygon{
        using shared_points =  std::shared_ptr<PointF>;
        Polygon(){}
        Polygon(size_t num){
            set_num(num);
        }
        Polygon(const std::vector<PointF>& vecs){
            set_num(vecs.size());
            for(int i = 0; i < vecs.size(); i++){
                set_point(i, vecs[i]);
            }
        }
        void set_num(size_t num){
            _size = num;
            _points.reset(new PointF[_size]);
        }

        size_t get_size() const {
            return _size;
        }
        shared_points points(){
            return _points;
        }

        void set_point(int32_t i, const PointF& point){
            reinterpret_cast<PointF*>(_points.get())[i] = point;
        }

         PointF point(int32_t i)  {
            return reinterpret_cast<PointF*>(_points.get())[i];
        }

        const PointF point(int32_t i) const {
            return reinterpret_cast<PointF*>(_points.get())[i];
        }

    private:
        shared_points _points;
        size_t  _size;
    };
}

#endif //OTL_COMMON_STRUCT_H
