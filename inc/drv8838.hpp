#pragma once

#include <cstdint>

class PololuDriver
{
    public:
        PololuDriver(uint8_t id);
        ~PololuDriver();

        void init();
        void enable();
        void disable();
        void setDirection(uint8_t direction);
        void setSpeed();
        void moveForward();
        void moveBackward();
        void sleep();

    private:
        uint8_t _id;
};