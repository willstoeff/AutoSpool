#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>

#include "motor.hpp"
#include "drv8838.hpp"
#include "gpio.hpp"
#include "heartbeat.hpp"

LOG_MODULE_REGISTER(main);

static const struct pwm_dt_spec servo = PWM_DT_SPEC_GET(DT_NODELABEL(pwm_output));
static const uint32_t min_pulse = DT_PROP(DT_NODELABEL(pwm_output), min_pulse);
static const uint32_t max_pulse = DT_PROP(DT_NODELABEL(pwm_output), max_pulse);

int main(void)
{
	heartbeat_init();

	if (!gpio_init())
	{
		LOG_ERR("GPIO init failed");
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