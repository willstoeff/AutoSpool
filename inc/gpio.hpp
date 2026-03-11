#pragma once

#include <zephyr/drivers/gpio.h>

extern const struct gpio_dt_spec enable_pin;
extern const struct gpio_dt_spec phase_pin;
extern const struct gpio_dt_spec sleep_pin;

int gpio_init();
int led_init();
int output_init();
int toggle_device_led();