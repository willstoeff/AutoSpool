#pragma once

#include "motor.hpp"
#include "drv8838.hpp"
#include "gpio.hpp"
#include "heartbeat.hpp"

int move_forward();
int move_backward();
int motor_sleep();
int motor_wake();