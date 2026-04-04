/**
 * @file main.cpp
 * @brief Main file
 *
 * @author William Stoeffhaas
 * @date 4/2/26
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#include "main.hpp"

LOG_MODULE_REGISTER(main);

int main(void)
{
	heartbeat_init();
	message_queue_init();

	if (!gpio_init())
	{
		LOG_ERR("GPIO init failed");
	}

    PololuDriver pololu_driver(enable_pin, phase_pin, sleep_pin, pwm);
	Motor<PololuDriver> driver(pololu_driver);
	pololu_driver.init();

	motor_msg_t msg;
	while (true) 
	{
		k_msgq_get(&motor_msgq, &msg, K_FOREVER);
		switch (msg.data_type)
		{
			case MOTOR_MOVE:
				driver.move(static_cast<Motor_Direction>(msg.data));
				break;
			case MOTOR_SPEED:
				driver.setSpeed(msg.data);
				break;
			case MOTOR_SLEEP:
				driver.sleep();
				break;
			default:
				LOG_ERR("Invalid Command: %d", msg.data_type);
		}
	}
	return 0;
}