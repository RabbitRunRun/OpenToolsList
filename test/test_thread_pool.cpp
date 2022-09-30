//
// Created by woshi on 2022/9/26.
//

#include <iostream>

#include "otl/thread/thread.h"
#include "otl/thread/thread_pool.h"
#include <string>
#include <sstream>

std::atomic<int> g_counter(0);
class Engine {
public:
    explicit Engine() {};
    void show() const {
        std::cout<<"Working thread id: " << std::this_thread::get_id()<< " Got counter: " << ++g_counter << std::endl;
    }
    const std::string get_message() {
        std::ostringstream  oss;
        oss << "Working thread id : ";
        oss << std::this_thread::get_id();
        return oss.str();
    }
};

int main() {
    const int N = 100;
    std::string strings[N];

    Engine engines[4];
    otl::ThreadPool thread_pool(4);
    for (int i = 0; i < N; ++i) {
        thread_pool.run([&engines, i, &strings](int id) {
            strings[i] = engines[id].get_message();
        });
    }
    thread_pool.join();

    for (int i = 0; i < N; ++i) {
        std::cout<< strings[i] << std::endl;
    }

    std::cout<<"We have result counter: " << g_counter << std::endl;
    return 0;
}