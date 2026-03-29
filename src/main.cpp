#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#include "main.hpp"

LOG_MODULE_REGISTER(main);

static bool inc_speed = false;

int main(void)
{
	heartbeat_init();
	message_queue_init();

	if (!gpio_init())
	{
		LOG_ERR("GPIO init failed");
	}

    PololuDriver driver(enable_pin, phase_pin, sleep_pin, pwm);
	Motor<PololuDriver> pololu_driver(driver);
	pololu_driver.init();

	static uint32_t speed = 0;
	motor_msg_t msg;
	while (true) 
	{
		while (1) 
		{
        	k_msgq_get(&motor_msgq, &msg, K_FOREVER);
			switch (msg.data_type)
			{
				case MOTOR_MOVE:
					pololu_driver.move(static_cast<Motor_Direction>(msg.data));
					break;
				case MOTOR_SPEED:
					pololu_driver.setSpeed(msg.data);
					break;
				case MOTOR_SLEEP:
					pololu_driver.sleep();
					break;
				default:
					LOG_ERR("Invalid Command: %d", msg.data_type);
			}
		}
	}

	return 0;
}