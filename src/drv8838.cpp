#include <stdio.h>
#include "drv8838.hpp"
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(pololu_driver);

PololuDriver::PololuDriver(uint8_t id):
    _id(id)
{
    LOG_INF("pololu constructor'd");
}

PololuDriver::~PololuDriver()
{

}

void PololuDriver::init()
{
    LOG_INF("pololu init'd");
}