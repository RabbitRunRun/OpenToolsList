//
// Created by woshi on 2022/9/26.
//

#include <iostream>

#include "otl/thread/thread.h"
#include "otl/thread/thread_pool.h"

std::atomic<int> g_counter(0);
class Engine {
public:
    explicit Engine() {};
    void show() const {
        std::cout<<"Working thread id: " << std::this_thread::get_id << " Got counter: " << ++g_counter << std::endl;
    }
};

int main() {
    Engine engines[4];
    otl::ThreadPool thread_pool(4);
    for (int i = 0; i < 344; ++i) {
        thread_pool.run([&](int id) {
            engines[id].show();
        });
    }
    thread_pool.join();
    std::cout<<"We have result counter: " << g_counter << std::endl;
    return 0;
}