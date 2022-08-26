//
// Created by kevin on 2022/8/25.
//
#include <iostream>
#include "otl/image/image.h"
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
    return 0;
}
