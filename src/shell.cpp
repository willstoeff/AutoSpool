#include <zephyr/shell/shell.h>

#include "main.hpp"

SHELL_CMD_REGISTER(toggle, NULL, "Toggle LED", toggle_device_led);
SHELL_CMD_REGISTER(move_forward, NULL, "Move motor forawrd", move_forward);
SHELL_CMD_REGISTER(move_backward, NULL, "Move motor forawrd", move_backward);
SHELL_CMD_REGISTER(sleep, NULL, "Move motor forawrd", motor_sleep);
SHELL_CMD_REGISTER(wake, NULL, "Move motor forawrd", motor_wake);
