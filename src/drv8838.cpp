#include <stdio.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/pwm.h>

#include "drv8838.hpp"

LOG_MODULE_REGISTER(pololu_driver);

PololuDriver::PololuDriver( const struct gpio_dt_spec enable_pin,
                            const struct gpio_dt_spec phase_pin,
                            const struct gpio_dt_spec sleep_pin,
                            const struct pwm_dt_spec pwm_pin):
    enable_pin_(enable_pin), phase_pin_(phase_pin), sleep_pin_(sleep_pin), pwm_pin_(pwm_pin) 
{
    LOG_INF("pololu constructor'd");
    state_ = MOTOR_UNKNOWN;
}

PololuDriver::~PololuDriver(){}

void PololuDriver::init()
{
    LOG_INF("Pololu Init");
    state_ = MOTOR_IDLE;
    speed_ = 0;
}

void PololuDriver::enable()
{
    if(state_ == MOTOR_UNKNOWN)
    {
        LOG_ERR("Motor in UNKNOWN state");
        return;
    }

    LOG_INF("Enable Driver");
    int ret = pwm_set_pulse_dt(&pwm_pin_, PWM_USEC(speed_));
    wake();
    state_ == MOTOR_MOVING;
}

void PololuDriver::disable()
{
    if(state_ == MOTOR_UNKNOWN)
    {
        LOG_ERR("Motor in UNKNOWN state");
        return;
    }
    LOG_INF("Disable Driver");
    int ret = pwm_set_pulse_dt(&pwm_pin_, PWM_USEC(0));
    state_ = MOTOR_STOPPED;
}


/**
 * @brief Set the duty cycle in microseconds.
 *
 * @param speed On time or duty cycle (in microseconds) set to the PWM.
 *
 * @return Nothing yet
 *
 */
void PololuDriver::setSpeed(uint32_t speed)
{
    if(state_ == MOTOR_UNKNOWN)
    {
        LOG_ERR("Motor in UNKNOWN state");
        return;
    }
    speed_ = speed;
    LOG_INF("Setting on time to %dus", speed_);
    if (state_ == MOTOR_MOVING)
    {
        enable();
    }
}

void PololuDriver::setDirection(Motor_Direction direction)
{
    LOG_INF("Set Direction");
    gpio_pin_set_dt(&phase_pin_, direction);
}

void PololuDriver::moveForward()
{
    if(state_ == MOTOR_UNKNOWN)
    {
        LOG_ERR("Motor in UNKNOWN state");
        return;
    }
    LOG_INF("Moving Forward");
    disable();
    setDirection(MOTOR_FORWARD);
    enable();
    state_ = MOTOR_MOVING;
}

void PololuDriver::moveBackward()
{
    if(state_ == MOTOR_UNKNOWN)
    {
        LOG_ERR("Motor in UNKNOWN state");
        return;
    }
    LOG_INF("Moving Backward");
    disable();
    setDirection(MOTOR_BACKWARD);
    enable();
    state_ = MOTOR_MOVING;

}

void PololuDriver::sleep()
{
    if(state_ == MOTOR_UNKNOWN)
    {
        LOG_ERR("Motor in UNKNOWN state");
        return;
    }
    LOG_INF("Sleep");
    gpio_pin_set_dt(&sleep_pin_, 0);
    state_ = MOTOR_IDLE;
}

void PololuDriver::wake()
{
    if(state_ == MOTOR_UNKNOWN)
    {
        LOG_ERR("Motor in UNKNOWN state");
        return;
    }
    LOG_INF("Wake");
    gpio_pin_set_dt(&sleep_pin_, 1);
    state_ = MOTOR_MOVING;
}
