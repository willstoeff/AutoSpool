#pragma once

#include <cstdint>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>

class PololuDriver
{
    public:
        PololuDriver(   const struct gpio_dt_spec enable_pin, 
                        const struct gpio_dt_spec phase_pin, 
                        const struct gpio_dt_spec sleep_pin,
                        const struct pwm_dt_spec pwm_pin);
        ~PololuDriver();

        void init();
        void enable();
        void disable();
        void setSpeed(uint32_t speed);
        void setDirection(uint8_t direction);
        void moveForward();
        void moveBackward();
        void sleep();
        void wake();

    private:
        uint8_t _id;
        const struct gpio_dt_spec _enable_pin;
        const struct gpio_dt_spec _phase_pin;
        const struct gpio_dt_spec _sleep_pin;
        const struct pwm_dt_spec _pwm_pin;

};