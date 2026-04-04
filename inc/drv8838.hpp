#pragma once

#include <cstdint>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>

#include "motor_types.hpp"

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
        void setDirection(Motor_Direction direction);
        void moveForward();
        void moveBackward();
        void sleep();
        void wake();

    private:
        Motor_State state_;
        uint8_t id_;
        uint8_t speed_;
        const struct gpio_dt_spec enable_pin_;
        const struct gpio_dt_spec phase_pin_;
        const struct gpio_dt_spec sleep_pin_;
        const struct pwm_dt_spec pwm_pin_;

};