#include "gpio.hpp"

#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int led_init()
{
	int ret = 0;
    if (!gpio_is_ready_dt(&led)) 
    {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}
    return 1;
}

int toggle_device_led()
{
	int ret;
	ret = gpio_pin_toggle_dt(&led);
	return ret;
}