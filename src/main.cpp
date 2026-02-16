#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>

#include "motor.hpp"
#include "drv8838.hpp"


LOG_MODULE_REGISTER(main);

#define SLEEP_TIME_MS   1000
#define LED0_NODE DT_ALIAS(led0)

int toggle_device_led();

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

SHELL_CMD_REGISTER(toggle, NULL, "Toggle LED", toggle_device_led);

int toggle_device_led()
{
	int ret;
	ret = gpio_pin_toggle_dt(&led);
	return ret;
}

int main(void)
{
	int ret;
	bool led_state = true;

	if (!gpio_is_ready_dt(&led)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}
    
    PololuDriver driver(1);
	Motor<PololuDriver> pololu_driver(driver);
	pololu_driver.init();

	return 0;
}