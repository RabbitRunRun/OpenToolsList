//
// Created by kevin on 2022/9/25.
//

#ifndef OTL_THREAD_H
#define OTL_THREAD_H

#include <thread>
#include <functional>
#include <memory>
#include <condition_variable>

namespace ts {
    class Thread {
    public:
        using self = Thread;
        using task_type = std::function<void(int)>;
        using after_task_type = std::function<void(int)>;

        Thread() = default;
        ~Thread();

        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;

        void run(const task_type& task);

        void run(const task_type& task, const after_task_type& after_task);

        void join();

        bool is_working();

    private:
        bool m_is_working;
        std::thread m_thread;
        std::condition_variable m_cv_core;
        std::mutex m_mutex;
        task_type  m_task = nullptr;
        after_task_type m_after_task  = nullptr;

    private:
        void working();
    };
}

#endif //OTL_THREAD_H
