#include <stdio.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/pwm.h>

#include "drv8838.hpp"

LOG_MODULE_REGISTER(pololu_driver);

PololuDriver::PololuDriver( const struct gpio_dt_spec enable_pin,
                            const struct gpio_dt_spec phase_pin,
                            const struct gpio_dt_spec sleep_pin,
                            const struct pwm_dt_spec pwm_pin):
    _enable_pin(enable_pin), _phase_pin(phase_pin), _sleep_pin(sleep_pin), _pwm_pin(pwm_pin) 
{
    LOG_INF("pololu constructor'd");
}

PololuDriver::~PololuDriver(){}

void PololuDriver::init()
{
    LOG_INF("Pololu Init");
}

void PololuDriver::enable()
{
    LOG_INF("Enable Driver");
    gpio_pin_set_dt(&_sleep_pin, 0);
    int ret = pwm_set_pulse_dt(&_pwm_pin, PWM_USEC(_speed));
}

void PololuDriver::disable()
{
    LOG_INF("Disable Driver");
    int ret = pwm_set_pulse_dt(&_pwm_pin, PWM_USEC(0));
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
    LOG_INF("Setting on time to %dus", speed);
    _speed = speed;
}

void PololuDriver::setDirection(uint8_t direction)
{
    LOG_INF("Set Direction");
    gpio_pin_set_dt(&_phase_pin, direction);
}

void PololuDriver::moveForward()
{
    LOG_INF("Moving Forward");
    disable();
    setDirection(1);
    enable();
}

void PololuDriver::moveBackward()
{
    LOG_INF("Moving Backward");
    disable();
    setDirection(0);
    enable();
}

void PololuDriver::sleep()
{
    LOG_INF("Sleep");
    gpio_pin_set_dt(&_sleep_pin, 1);
    disable();
}

void PololuDriver::wake()
{
    LOG_INF("Wake");
    gpio_pin_set_dt(&_sleep_pin, 0);
}
