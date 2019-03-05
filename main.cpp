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
#include <functional>
#include "TimerTask.h"
#include "SensorCore.h"
#include "FObserver.h"

class Foo : public FObserver::Observer{
public:
    void notify(const std::string& data) override {
        std::cout << "Foo::notify: " << data << std::endl;
    }
};

int main()
{
    std::cout << "Starting..." << std::endl;
    TempSensor::TimerTask tt;
    TempSensor::SensorCore core("28-0417a2f482ff");
    Foo f;
    core.register_observer(f);

    std::thread t1 = tt.thread_run(std::bind(&TempSensor::SensorCore::readSensor, &core));
    t1.join();

    return 0;
}
