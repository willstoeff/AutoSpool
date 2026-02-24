#include <zephyr/shell/shell.h>

#include "gpio.hpp"

SHELL_CMD_REGISTER(toggle, NULL, "Toggle LED", toggle_device_led);
