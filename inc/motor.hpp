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

        void setSpeed(uint32_t speed)
        {
            LOG_MODULE_DECLARE(main);
            LOG_INF("Motor Set Speed");
            _driver.setSpeed(speed);
        }

        void setDirection(Motor_Direction direction)
        {
            LOG_MODULE_DECLARE(main);
            LOG_INF("Motor Set Direction");
            uint8_t dir;
            if (direction == MOTOR_FORWARD)
            {
                dir = 1;
            }
            else if (direction == MOTOR_BACKWARD)
            {
                dir = 0;
            }
            else
            {
                LOG_INF("Motor Direction Error: %d", static_cast<uint8_t>(direction));
                return;
            }

            _driver.setDirection(dir);
        }

        void moveForward()
        {
            LOG_MODULE_DECLARE(main);
            LOG_INF("Motor Move Forward");
            _driver.moveForward();
        }

        void moveBackward()
        {
            LOG_MODULE_DECLARE(main);
            LOG_INF("Motor Move Backward");
            _driver.moveBackward();
        }

        void sleep()
        {
            LOG_MODULE_DECLARE(main);
            LOG_INF("Motor Sleep");
            _driver.sleep();
        }

        void wake()
        {
            LOG_MODULE_DECLARE(main);
            LOG_INF("Motor Wake");
            _driver.wake();
        }

    private:
        Driver& _driver;
};