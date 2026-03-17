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
    LOG_INF("Pololu Init");
}

void PololuDriver::enable()
{
    LOG_INF("Enable Driver");
    gpio_pin_set_dt(&_sleep_pin, 0);
    gpio_pin_set_dt(&_enable_pin, 1);	
}

void PololuDriver::disable()
{
    LOG_INF("Disable Driver");
    gpio_pin_set_dt(&_enable_pin, 0);
}

void PololuDriver::setSpeed(uint8_t speed)
{
    LOG_INF("setSpeed");
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
}

void PololuDriver::wake()
{
    LOG_INF("Wake");
    gpio_pin_set_dt(&_sleep_pin, 0);
}
