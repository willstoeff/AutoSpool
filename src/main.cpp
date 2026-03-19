#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/pwm.h>

#include "motor.hpp"
#include "drv8838.hpp"
#include "gpio.hpp"

LOG_MODULE_REGISTER(main);

static const struct pwm_dt_spec pwm = PWM_DT_SPEC_GET(DT_NODELABEL(pwm_output));

int main(void)
{
	if (!gpio_init())
	{
		LOG_ERR("LED init failed");
	}

    PololuDriver driver(enable_pin, phase_pin, sleep_pin);
	Motor<PololuDriver> pololu_driver(driver);
	pololu_driver.init();
	
	while (true) 
	{
		k_sleep(K_FOREVER);
	}

	return 0;
}