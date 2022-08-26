//
// Created by woshi on 2022/8/25.
//

#ifndef OTL_IMAGE_STRUCT_H
#define OTL_IMAGE_STRUCT_H
#include <memory>
#include <cstdint>
#include "otl/utils/assert.h"
namespace otl{
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

        template <typename Dtype>
        Image(int32_t width, int32_t height, int32_t channels, Dtype* data_from) : Image(width, height, channels){
            if(data_from) load(data_from);
        }

        void set_width(int32_t width){m_width = width;}
        int32_t  get_width() const {
            return m_width;
        }

        void set_height(int32_t height){m_height = height;}
        int32_t get_height() const {
            return m_height;
        }

        void set_channels(int32_t channels){m_channels = channels;}
        int32_t get_channels() const {
            return m_channels;
        }

        void fill_zeros(){
            if(m_data == nullptr) {
                int len = m_width * m_height * m_channels;
                m_data.reset(new T[len]);
                memset(m_data.get(), 0, sizeof(T) * len);
            }
        }

        template <typename Dtype>
        void load(Dtype* data_from){
            if(data_from == nullptr) return;
            int data_len = m_width * m_height * m_channels;
            int mem_used = data_len * sizeof(T);
            m_data.reset(new T[m_width * m_height * m_channels]);
            memcpy_s(m_data.get(), mem_used, data_from, mem_used);
        }

#define OTL_LOCATION(h,w,c) ((h * m_width + w ) * m_channels + c)

        T at(size_t h, size_t w, size_t c){
            OTL_ASSERT(h < m_height);
            OTL_ASSERT(w < m_width);
            OTL_ASSERT(c < m_channels);
            size_t location = OTL_LOCATION(h, w, c);
            return *(reinterpret_cast<T*>(m_data.get()) + location);
        }

        void set(size_t h, size_t w, size_t c, T value){
            OTL_ASSERT(h < m_height);
            OTL_ASSERT( w < m_width);
            OTL_ASSERT(c < m_channels);
            size_t location = OTL_LOCATION(h, w, c);
            *(reinterpret_cast<T*>(m_data.get()) + location) = value;
        }
#undef OTL_LOCATION

        self& operator=(const self &other){
            this->m_width = other.m_width;
            this->m_height = other.m_height;
            this->m_channels = other.m_channels;
            this->m_data = other.m_data;
            return *this;
        }

    private:
        std::shared_ptr<T> m_data;
        int m_width;
        int m_height;
        int m_channels;
    };
    template class Image<char>;

    template class Image<unsigned char>;

    template class Image<float>;

    template class Image<double>;
}

#endif //OTL_IMAGE_STRUCT_H
