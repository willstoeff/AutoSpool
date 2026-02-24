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
    LOG_INF("pololu init'd");
}