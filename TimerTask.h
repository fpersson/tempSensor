//
// Created by fredrik on 2019-03-05.
//

#ifndef TEMPSENSOR_TIMERTASK_H
#define TEMPSENSOR_TIMERTASK_H

#include <chrono>
#include <thread>
#include <functional>
#include <atomic>

namespace TempeSensor {
    class TimerTask {
    public:
        explicit TimerTask(long minutes = 1);
        void run(std::function<void()>);
        std::thread thread_run(std::function<void()>);
        void interrupt();
    private:
        long mDelay;
        void sleep();
        std::atomic<bool> mRunning;
    };
}


#endif //TEMPSENSOR_TIMERTASK_H
