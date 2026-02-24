#include <stdio.h>
#include <zephyr/logging/log.h>

#include "drv8838.hpp"

LOG_MODULE_REGISTER(pololu_driver);

PololuDriver::PololuDriver(uint8_t id):
    _id(id)
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
}

void PololuDriver::disable()
{
    LOG_INF("disable");
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

