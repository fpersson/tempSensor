//
// Created by fredrik on 2019-03-05.
//

#include <iostream>
#include <thread>
#include <functional>
#include "TimerTask.h"

namespace TempeSensor{

    TimerTask::TimerTask(long minutes) :mDelay(minutes) {
        std::cout << "Delay: " << mDelay << std::endl;
    }

    void TimerTask::run(std::function<void()>callback) {
        mRunning = true;
        while(mRunning){
            callback();
            this->sleep();
        }
    }

    std::thread TimerTask::thread_run(std::function<void()> callback) {
        mRunning = true;
        return std::thread( [=] {
            while(mRunning){
                callback();
                this->sleep();
            }
        });
    }

    void TimerTask::sleep() {
        std::this_thread::sleep_for(std::chrono::minutes(mDelay));
    }

    void TimerTask::interrupt() {
        mRunning = false;
    }

}
