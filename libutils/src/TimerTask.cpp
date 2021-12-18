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

    TimerTask::TimerTask(long minutes) :mDelay(minutes) {;}

    void TimerTask::run(const std::function<void()>&callback) {
        mRunning.store(true);
        while(mRunning.load()){
            callback();
            this->sleep();
        }
    }

    std::thread TimerTask::thread_run(const std::function<void()>& callback) {
        mRunning.store(true);
        return std::thread( [=] {
            while(mRunning.load()){
                callback();
                this->sleep();
            }
        });
    }

    void TimerTask::sleep() const {
        std::this_thread::sleep_for(std::chrono::minutes(mDelay));
    }

    void TimerTask::interrupt() {
        mRunning.store(false);
    }

}
