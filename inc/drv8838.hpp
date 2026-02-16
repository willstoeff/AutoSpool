#pragma once

#include <cstdint>

class PololuDriver
{
    public:
        PololuDriver(uint8_t id);
        ~PololuDriver();

        void init();

    private:
        uint8_t _id;
};