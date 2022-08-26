//
// Created by kevin on 2022/8/25.
//
#include <iostream>
#include "otl/image/image.h"
#include "otl/image/common_struct.h"
#include "otl/image/image_general.h"
#ifdef OTL_WITH_OPENCV
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#endif
#include <algorithm>
#include <cmath>
#include <chrono>
using namespace std::chrono;
int main(){
    otl::Image<unsigned char> image(100, 100, 3);
    image.fill_zeros();
    std::cout<< (int)image.at(20, 30 , 1) <<std::endl;
    image.set(20, 30, 1, (unsigned  char)127);
    std::cout<< (int)image.at(20, 30 , 1) <<std::endl;

    otl::Image<float> image_float(10, 19, 4);
    image_float.fill_zeros();
    image_float.set(5, 5, 0, 0.1f);
    std::cout << image_float.at(5, 5, 0) << std::endl;

#ifdef OTL_WITH_OPENCV
    cv::Scalar blue(255, 0, 0);
    cv::Scalar green(0, 255, 0);
    cv::Scalar red(0, 0, 255);

    float coefficient = 2.0f;
    std::vector<otl::PointF> vec_points = {{coefficient * 85, coefficient *  50}, {coefficient *  110, coefficient * 75},
                                           {coefficient * 135, coefficient * 100},{coefficient * 135, coefficient * 75},
                                            {coefficient *  15, coefficient * 100}, {coefficient * 15, coefficient * 75},
                                            {coefficient * 35, coefficient * 75}, {coefficient * 60, coefficient * 50}};
    otl::Polygon poly(vec_points);
    int32_t contour_min_x = INT_MAX;
    int32_t contour_max_x = 0;
    int32_t contour_min_y = INT_MAX;
    int32_t contour_max_y = 0;

    for(int i = 0; i < vec_points.size(); ++i){
        contour_min_x = std::min(contour_min_x, (int)vec_points[i].x);
        contour_max_x = std::max(contour_max_x, (int)vec_points[i].x);
        contour_min_y = std::min(contour_min_y, (int)vec_points[i].y);
        contour_max_y = std::max(contour_max_y, (int)vec_points[i].y);
    }

    int32_t image_width = 600;
    int32_t image_height = 600;
    cv::Mat mat = cv::Mat(image_width,  image_height, CV_8UC3);
    memset(mat.data, 0, image_width * image_height * 3);
//    cv::imshow("test for polygon", mat);

    for(int i = contour_min_x; i <= contour_max_x; i++){
        for(int j = contour_min_y; j < contour_max_y; j++){
//            std::cout<<i <<", "<<j<<std::endl;
            otl::PointF point;
            point.x = i;
            point.y = j;
            auto start = system_clock::now();
            bool in_poly = otl::point_in_polygon(image_width, image_height, poly, point);
            auto end = system_clock::now();
            float spent = duration_cast<milliseconds>(end - start).count();
            std::cout<<"point in polygon judge spent " <<spent <<" ms"<<std::endl;

            if(in_poly){
                cv::circle(mat, cv::Point(i, j), 1, blue);
            }
        }
    }
    cv::rectangle(mat, cv::Point(contour_min_x, contour_min_y), cv::Point(contour_max_x, contour_max_y), green, 2);
    cv::imshow("test for polygon", mat);
    while(true){
        if(cv::waitKey(10) >= 27)
        break;
    }
#endif
    return 0;
}
