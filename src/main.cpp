#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>

#include "motor.hpp"
#include "drv8838.hpp"
#include "gpio.hpp"

LOG_MODULE_REGISTER(main);

#define HEARTBEAT_THREAD_STACK_SIZE 500
#define HEARTBEAT_THREAD_PRIORITY 5

void heartbeat_entry(void*, void*, void*)
{
	for(;;)
	{
		if (toggle_device_led())
		{
			LOG_ERR("LED error");
		}
		k_sleep(K_MSEC(500));
	}
}

K_THREAD_DEFINE(heartbeat_thread, HEARTBEAT_THREAD_STACK_SIZE, heartbeat_entry, 
			NULL, NULL, NULL, 
			HEARTBEAT_THREAD_PRIORITY, 0, 0);	

static const struct pwm_dt_spec servo = PWM_DT_SPEC_GET(DT_NODELABEL(pwm_output));
static const uint32_t min_pulse = DT_PROP(DT_NODELABEL(pwm_output), min_pulse);
static const uint32_t max_pulse = DT_PROP(DT_NODELABEL(pwm_output), max_pulse);

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