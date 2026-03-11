#include <stdio.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#include "drv8838.hpp"

LOG_MODULE_REGISTER(pololu_driver);

PololuDriver::PololuDriver( const struct gpio_dt_spec enable_pin,
                            const struct gpio_dt_spec phase_pin,
                            const struct gpio_dt_spec sleep_pin):
    _enable_pin(enable_pin), _phase_pin(phase_pin), _sleep_pin(sleep_pin) 
{
    LOG_INF("pololu constructor'd");
}

PololuDriver::~PololuDriver(){}

void PololuDriver::init()
{
    LOG_INF("pololu init");
    //set GPIOs for dir, pwm, etc
}

void PololuDriver::enable()
{
    LOG_INF("enable");
    gpio_pin_set_dt(&_enable_pin, 1);	
}

void PololuDriver::disable()
{
    LOG_INF("disable");
    gpio_pin_set_dt(&_enable_pin, 0);
}

void PololuDriver::setDirection(uint8_t direction)
{
    LOG_INF("setDirection");
}

void PololuDriver::setSpeed()
{
    LOG_INF("setSpeed");
}

void PololuDriver::moveForward()
{
    LOG_INF("moveForward");
}

void PololuDriver::moveBackward()
{
    LOG_INF("moveBackward");
}

void PololuDriver::sleep()
{
    LOG_INF("Sleep");
}

