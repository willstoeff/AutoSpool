#pragma once

#include <zephyr/drivers/gpio.h>

int gpio_init();
int led_init();
int output_init();
int toggle_device_led();