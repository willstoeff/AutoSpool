#include "gpio.hpp"

#define LED0_NODE DT_ALIAS(led0)
#define ENABLE_OUTPUT DT_ALIAS(enable0)
#define PHASE_OUTPUT DT_ALIAS(phase0)
#define SLEEP_OUTPUT DT_ALIAS(sleep0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec enable = GPIO_DT_SPEC_GET(ENABLE_OUTPUT, gpios);
static const struct gpio_dt_spec phase = GPIO_DT_SPEC_GET(PHASE_OUTPUT, gpios);
static const struct gpio_dt_spec sleep = GPIO_DT_SPEC_GET(SLEEP_OUTPUT, gpios);

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

int output_init()
{
	int ret = 0;
    if (!gpio_is_ready_dt(&enable)) 
    {
		return 0;
	}

	ret = gpio_pin_configure_dt(&enable, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

    if (!gpio_is_ready_dt(&phase)) 
    {
		return 0;
	}

	ret = gpio_pin_configure_dt(&phase, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	if (!gpio_is_ready_dt(&sleep)) 
    {
		return 0;
	}

	ret = gpio_pin_configure_dt(&sleep, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

    return 1;
}

int gpio_init()
{
	int ret = 0;
	ret = output_init();
	ret |= led_init();
	return ret;
}

int toggle_device_led()
{
	int ret;
	ret = gpio_pin_toggle_dt(&led);
	ret |= gpio_pin_toggle_dt(&enable);
	ret |= gpio_pin_toggle_dt(&phase);
	ret |= gpio_pin_toggle_dt(&sleep);
	return ret;
}