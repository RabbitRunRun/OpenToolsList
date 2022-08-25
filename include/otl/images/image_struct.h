//
// Created by woshi on 2022/8/25.
//

#ifndef OTL_IMAGE_STRUCT_H
#define OTL_IMAGE_STRUCT_H
#include <memory>
#include <cstdint>
template <typename T>
class Image{
public:
    using self = Image<T>;
    Image():Image(0){}
    Image(int32_t size):Image(size, size){}
    Image(int32_t width, int32_t height):Image(width, height, 3){}
    Image(int32_t width, int32_t height, int32_t channels){
        m_width = width;
        m_height = height;
        m_channels = channels;
    }
    void set_width(int32_t width){m_width = width;}
    void set_height(int32_t height){m_height = height;}
    void set_channels(int32_t channels){m_channels = channels;}

    template <typename Dtype>
    void load(Dtype* data_from){
        int data_len = m_width * m_height * m_channels;
        int mem_used = data_len * sizeof(T);
        m_data.reset(new T[m_width * m_height * m_channels]);
        memcpy_s(m_data.get(), mem_used, data_from, mem_used);
    }

    self operator=(const self &other){}
    self operator=(const self&& other){}
private:
    std::shared_ptr<T> m_data;
    int m_width;
    int m_height;
    int m_channels;
};
struct PointF{
    float x;
    float y;
};
#endif //OTL_IMAGE_STRUCT_H
