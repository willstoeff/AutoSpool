#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#include "main.hpp"

LOG_MODULE_REGISTER(main);

static bool inc_speed = false;

int update_speed()
{
	inc_speed = true;
	return true;
}

int main(void)
{
	heartbeat_init();

	if (!gpio_init())
	{
		LOG_ERR("GPIO init failed");
	}

    PololuDriver driver(enable_pin, phase_pin, sleep_pin, pwm);
	Motor<PololuDriver> pololu_driver(driver);
	pololu_driver.init();

	static uint32_t speed = 0;

	while (true) 
	{
		if(inc_speed)
		{
			inc_speed = false;
			speed += 2;
			if (speed > 10) 
			{
				speed = 0;
			}
			pololu_driver.setSpeed(speed);
		}
		k_sleep(K_MSEC(1));
	}

	return 0;
}