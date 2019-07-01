/*
    Copyright (C) 2019, Fredrik Persson <fpersson.se@gmail.com>

    Permission to use, copy, modify, and/or distribute this software
    for any purpose with or without fee is hereby granted.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
    AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
    INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
    OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
    OF THIS SOFTWARE.
 */

#include <iostream>
#include <thread>
#include <functional>
#include "TimerTask.h"

namespace TempSensor{

    TimerTask::TimerTask(long minutes) :mDelay(minutes) {
#ifdef DEBUGMODE
        std::cout << "Delay: " << mDelay << std::endl;
#endif
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
