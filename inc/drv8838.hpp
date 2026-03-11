#pragma once

#include <cstdint>

class PololuDriver
{
    public:
        PololuDriver(   const struct gpio_dt_spec enable_pin, 
                        const struct gpio_dt_spec phase_pin, 
                        const struct gpio_dt_spec sleep_pin);
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
        const struct gpio_dt_spec _enable_pin;
        const struct gpio_dt_spec _phase_pin;
        const struct gpio_dt_spec _sleep_pin;

};