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


#ifndef TEMPSENSOR_TIMERTASK_H
#define TEMPSENSOR_TIMERTASK_H

#include <chrono>
#include <thread>
#include <functional>
#include <atomic>

namespace TempSensor {
    class TimerTask {
    public:
        explicit TimerTask(long minutes = 1);
        void run(const std::function<void()>&);
        std::thread thread_run(const std::function<void()>&);
        void interrupt();
    private:
        long mDelay;
        void sleep() const;
        std::atomic<bool> mRunning{};
    };
}


#endif //TEMPSENSOR_TIMERTASK_H
