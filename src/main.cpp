#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#include "motor.hpp"
#include "drv8838.hpp"
#include "gpio.hpp"

LOG_MODULE_REGISTER(main);

int main(void)
{
	//init the IO
	if (!led_init())
	{
		LOG_ERR("LED init failed");
	}

    PololuDriver driver(1);
	Motor<PololuDriver> pololu_driver(driver);
	pololu_driver.init();
	
	while (true) 
	{
		k_sleep(K_FOREVER);
	}

	return 0;
}