//
// Created by pierre on 20/11/2018.
//

#pragma once

#include <chrono>
#include <ctime>

namespace game {
    struct Firerate {
        Firerate() {}
        Firerate(int firerate)
        {
            _firerate = firerate;
        }

        int     _firerate = 1000;
        std::chrono::time_point<std::chrono::system_clock>     _lastfire;
    };
}