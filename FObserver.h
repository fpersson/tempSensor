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

#ifndef TEMPSENSOR_FOBSERVER_H
#define TEMPSENSOR_FOBSERVER_H

#include <iostream>
#include <vector>
#include <functional>


namespace FObserver{

    class Observer{
    public:
        virtual void notify(const std::string& data)=0;
    };

    class Observable{
    public:
        void register_observer(Observer& o){
            observers.emplace_back(o);
        }

        void onEvent(const std::string& data ){
            for(Observer& o : observers){
                o.notify(data);
            }
        }

    private:
        std::vector<std::reference_wrapper<Observer>> observers;
    };
} //namespace

#endif //TEMPSENSOR_FOBSERVER_H
