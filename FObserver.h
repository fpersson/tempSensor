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
