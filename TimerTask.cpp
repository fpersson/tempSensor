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
