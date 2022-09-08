//
// Created by kevin on 2022/8/25.
//
#include <iostream>
#include "otl/image/image.h"
#include <stdlib.h>
#include <utility>
#include <functional>

namespace otl{
    class StaticAction {
    public:
        template <typename FUNC, typename... Args>
        explicit StaticAction(FUNC func, Args&&... args)  {
            std::bind(func, std::forward<Args>(args)...)();
        }
    };


#define _ts_concat_name_core(x,y) (x##y)

#define _ts_concat_name(x, y) _ts_concat_name_core(x,y)

/**
 * generate an serial name by line
 */
#define ts_serial_name(x) _ts_concat_name(x, __LINE__)

/**
 * Static action
 */
#define TS_STATIC_ACTION(func, ...) \
    namespace \
    { \
         otl::StaticAction ts_serial_name(_ts_static_action_)(func, ## __VA_ARGS__); \
    }

    static void test1(int a){
        std::cout<<a<<std::endl;
    }

    static void test2(int a, int b){
        std::cout<<a <<" "<<b<<std::endl;
    }

    static void test0(){
        std::cout<<"joke"<<std::endl;
    }

    TS_STATIC_ACTION(test0);

#define TS_SOLUTION_DIR R"(C:\D\self\DPCoding\OpenToolsList)"
#define TS_LOCAL_FILE ( \
    std::strlen(TS_SOLUTION_DIR) + 1 < std::strlen(__FILE__) \
    ? ((const char*)(__FILE__) + std::strlen(TS_SOLUTION_DIR) + 1) \
    : ((const char*)(__FILE__)) \
)
}
#include "otl/utils/implement.h"

class DeclareTester{
public:
    explicit DeclareTester(int a, int b, float c){
        m_a = a;
        m_b = b;
        m_c = c;
        std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
    }

public:
    int m_a;
    int m_b;
    float m_c;
};
int main(){
    std::cout<<TS_LOCAL_FILE<<std::endl;
    otl::Declare<int> dec_int(10);
    std::cout<< dec_int.operator*() <<std::endl;

    otl::Declare<DeclareTester> dec_dec_tester(10, 29, 9.9f);
    std::cout << dec_dec_tester.operator*().m_a << " " << dec_dec_tester.operator->()->m_c <<std::endl;

//    otl::Image<unsigned char> image(100, 100, 3);
//    image.fill_zeros();
//    std::cout<< (int)image.at(20, 30 , 1) <<std::endl;
//    image.set(20, 30, 1, (unsigned  char)127);
//    std::cout<< (int)image.at(20, 30 , 1) <<std::endl;
//
//    otl::Image<float> image_float(10, 19, 4);
//    image_float.fill_zeros();
//    image_float.set(5, 5, 0, 0.1f);
//    std::cout << image_float.at(5, 5, 0) << std::endl;
    return 0;
}
