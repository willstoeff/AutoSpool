#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>

#include "main.hpp"

LOG_MODULE_REGISTER(main);

static const struct pwm_dt_spec servo = PWM_DT_SPEC_GET(DT_NODELABEL(pwm_output));
static const uint32_t min_pulse = DT_PROP(DT_NODELABEL(pwm_output), min_pulse);
static const uint32_t max_pulse = DT_PROP(DT_NODELABEL(pwm_output), max_pulse);

static bool mf = false;
static bool mb = false;
static bool s = false;
static bool w = false;

int move_forward()
{
	mf = true;
	return true;
}

int move_backward()
{
	mb = true;
	return true;
}
int motor_sleep()
{
	s = true;
	return true;
}
int motor_wake()
{
	w = true;
	return true;
}

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
		if(mf == true)
		{
			mf = false;
			pololu_driver.moveForward();
		}
		if(mb == true)
		{
			mb = false;
			pololu_driver.moveBackward();
		}
		if(s == true)
		{
			s = false;
			pololu_driver.sleep();
		}
		if(w == true)
		{
			w = false;
			pololu_driver.wake();
		}
		k_sleep(K_MSEC(100));
	}

	return 0;
}