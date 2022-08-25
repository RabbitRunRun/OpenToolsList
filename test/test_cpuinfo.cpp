//
// Created by woshi on 2022/8/19.
//

#include <iostream>
#include "otl/utils/cpu_info.h"
#include <array>
#include <vector>
#include <bitset>

class StaticTester{
public:

    static int get(){
        return m_data;
    }
private:
    static int m_data;
};
int StaticTester::m_data = -2;

int main(int argc, char** argv){
    std::cout << StaticTester::get() << std::endl;

    std::array<int, 4> cpui;
    __cpuid(cpui.data(), 0);
    int max_code = cpui[0];
    std::cout<< max_code << std::endl;
    std::vector<std::array<int , 4> > data_;
    for ( int i = 0; i < max_code; ++i){
        __cpuidex(cpui.data(), i, 0);
        data_.push_back(cpui);
    }

    char vendor[0x20];
    memset(vendor, 0, sizeof(vendor));
    *reinterpret_cast<int*>(vendor) = data_[0][1];
    *reinterpret_cast<int*>(vendor + 4) = data_[0][3];
    *reinterpret_cast<int*>(vendor + 8) = data_[0][2];
    std::cout << "vendor name: " << vendor << std::endl;

//    int a = 1;
//    std::bitset<32> test = a;
//    for(int i = 0; i < 32; ++i){
//        std::cout << (bool)test[i] << std::endl;
//    }

    std::bitset<32> f_1_ECX_;
    std::bitset<32> f_1_EDX_;
    if (max_code >= 1){
        f_1_ECX_ = data_[1][2];
        f_1_EDX_ = data_[1][3];
    }

    std::bitset<32> f_7_EBX_;
    std::bitset<32> f_7_ECX_;

    if (max_code >= 7)
    {
        f_7_EBX_ = data_[7][1];
        f_7_ECX_ = data_[7][2];
    }

    auto& outstream = std::cout;
    auto support_message = [&outstream](std::string isa_feature, bool is_supported) {
        outstream << isa_feature << (is_supported ? " supported" : " not supported") << std::endl;
    };

    support_message("MMX", f_1_EDX_[23]);
    support_message("SSE", f_1_EDX_[25]);
    support_message("SSE2", f_1_EDX_[26]);
    support_message("AVX", f_1_ECX_[28]);
    support_message("AVX2", f_7_EBX_[5]);
    support_message("AVX512CD", f_7_EBX_[28]);
    return 0;
}