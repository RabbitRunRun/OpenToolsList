//
// Created by kevin on 2022/9/25.
//

#include "thread/thread.h"
#include <iostream>

namespace otl {
    Thread::Thread()
        : m_is_working(true), m_task(nullptr), m_after_task(nullptr){
        m_thread = std::thread(&Thread::working, this);
    }

    Thread::~Thread() {
       this->join();
    }

    void Thread::join() {
        {
            std::unique_lock<std::mutex> locker(m_mutex);
            m_is_working = false;
            m_task = nullptr;
            m_after_task = nullptr;
            m_cv_core.notify_all();
        }
//        std::cout<<"Thread begin to join." << std::endl;
        m_thread.join();
//        std::cout<<"Thread finished to join." << std::endl;
    }

    bool Thread::is_working() {
        return m_is_working;
    }

    void Thread::working() {
        std::unique_lock<std::mutex> locker(m_mutex);
        while(m_is_working) {
            while(m_is_working && !m_task) m_cv_core.wait(locker);
            if (!m_is_working) break;
            m_task(m_core_index);
            if (m_after_task) m_after_task(m_core_index);
            m_task = nullptr;
            m_after_task = nullptr;
            m_cv_core.notify_all();
        }
    }

    void Thread::run(int thread_index, const task_type &task) {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_task = task;
        m_core_index = thread_index;
        m_cv_core.notify_all();
    }

    void Thread::run(int thread_index, const task_type &task, const after_task_type &after_task) {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_task = task;
        m_after_task = after_task;
        m_core_index = thread_index;
        m_cv_core.notify_all();
    }

}