//
// Created by kevin on 2022/9/25.
//

#ifndef OTL_THREAD_POOL_H
#define OTL_THREAD_POOL_H

#include <vector>
#include <queue>
#include <atomic>

#include "thread/thread.h"

namespace ts {
    class ThreadPool {
    public:
        using self = ThreadPool;

        ThreadPool(int n);
        ~ThreadPool();

        ThreadPool(const ThreadPool&) = delete;
        ThreadPool& operator=(const ThreadPool&) = delete;

        Thread* run(const Thread::task_type &task);

        bool is_busy();

        void disable_working();

        void enable_working();

        void join();

        int get_worker_number();

    private:
        std::atomic<bool> m_is_working;
        std::atomic<int> m_core_number;
        std::vector<Thread*> m_thread_pool;
        std::queue<int> m_cores;
        std::condition_variable m_cv;
        std::mutex m_mutex;
    };
}
#endif //OTL_THREAD_POOL_H
