#include <zephyr/logging/log.h>

#include "pwm.hpp"

LOG_MODULE_REGISTER(pwm_module);

const struct pwm_dt_spec pwm = PWM_DT_SPEC_GET(DT_NODELABEL(pwm_output));
const uint32_t min_pulse = DT_PROP(DT_NODELABEL(pwm_output), min_pulse);
const uint32_t max_pulse = DT_PROP(DT_NODELABEL(pwm_output), max_pulse);

int pwm_init()
{
	if (!pwm_is_ready_dt(&pwm)) 
	{
		LOG_INF("Error: PWM device %s is not reasdady\n", pwm.dev->name);
		return 0;
	}
 
	uint32_t pulse_width = min_pulse;
	int ret = pwm_set_dt(&pwm, PWM_USEC(20), pulse_width);
    
    return 1;
}
