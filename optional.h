//
// Created by fredrik on 2019-04-06.
//

#ifndef TEMPSENSOR_OPTIONAL_H
#define TEMPSENSOR_OPTIONAL_H

#include <memory>

namespace utils{
    template <typename T>
    class option{
    public:
        option(T t) : mVal(std::make_unique<T>(t)){};

        T& operator*(){
            return *mVal;
        }

        static option<T> none(){
            return option<T>();
        }

        operator bool() const {
            return mVal != nullptr;
        }

    private:
        option() : mVal() {;}
        std::unique_ptr<T> mVal;
    };
}

#endif //TEMPSENSOR_OPTIONAL_H
