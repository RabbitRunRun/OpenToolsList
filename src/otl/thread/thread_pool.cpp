//
// Created by kevin on 2022/9/25.
//
#include <iostream>

#include "thread/thread_pool.h"

namespace otl {
    ThreadPool::ThreadPool(int n)
        : m_core_number(n), m_thread_pool(n){
        for (int i = 0; i < n; ++i) {
            m_thread_pool[i] = new Thread();
            m_cores.push(i);
        }
    }

    ThreadPool::~ThreadPool() {
        this->join();
    }

    void ThreadPool::join() {
        std::unique_lock<std::mutex> locker(m_mutex);
        while(m_cores.size() < m_thread_pool.size()) m_cv.wait(locker);

        for (int i = 0; i < m_core_number; ++i) {
            delete m_thread_pool[i];
        }
//        std::cout<<"ThreadPool Join finished" <<std::endl;
    }

    int ThreadPool::get_worker_number() {
        return m_core_number;
    }

    bool ThreadPool::is_busy() {
        std::unique_lock<std::mutex> locker(m_mutex);
        bool is_busy = (m_core_number > m_cores.size());
        return is_busy;
    }

    int ThreadPool::load() {
        std::unique_lock<std::mutex> locker(m_mutex);
        while(m_cores.empty()) m_cv.wait(locker);
        int id = m_cores.front();
        m_cores.pop();
        return id;
    }

    void ThreadPool::recycle(int id) {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_cores.push(id);
        m_cv.notify_all();
    }

    Thread * ThreadPool::run(const Thread::task_type &task) {
        if (m_core_number <= 0) {
            task(0);
            return nullptr;
        } else {
            int id = load();
//            std::cout << "inner thread id: " << id << std::endl;

            Thread* single_worker = m_thread_pool[id];

            single_worker->run(id, task, std::bind(&ThreadPool::recycle, this, std::placeholders::_1));
            return single_worker;
        }
    }
}
