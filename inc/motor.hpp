#pragma once
#include <zephyr/logging/log.h>

template <typename Driver> class Motor
{
    public:
        enum Motor_Direction: uint8_t
        {
            MOTOR_FORWARD = 0x00,
            MOTOR_BACKWARD,
            MOTOR_DIRECTION_ERROR
        };

        enum Motor_Error: uint8_t
        {
            MOTOR_NO_ERROR = 0x00,
            MOTOR_ERROR
        };

        explicit Motor(Driver& driver)
            : _driver(driver)
        {
            LOG_MODULE_DECLARE(main);
            LOG_INF("Motor constructor'd");
        }

        void init()
        {
            LOG_MODULE_DECLARE(main);
            LOG_INF("Motor init'd");
            _driver.init();
        }

    private:
        Driver& _driver;
};