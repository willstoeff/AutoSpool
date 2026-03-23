#include <zephyr/shell/shell.h>

#include "main.hpp"

SHELL_CMD_REGISTER(toggle, NULL, "Toggle LED", toggle_device_led);
SHELL_CMD_REGISTER(up, NULL, "Increase motor speed", update_speed);