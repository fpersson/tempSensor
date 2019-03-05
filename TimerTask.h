/*
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA  02110-1301, USA.

    ---
    Copyright (C) 2019, Fredrik Persson <fpersson.se@gmail.com>
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
