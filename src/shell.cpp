/**
 * @file shell.cpp
 * @brief 
 *
 *
 * @author William Stoeffhaas
 * @date 3/28/26
 */

#include <stdlib.h> 

#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>

#include "gpio.hpp"
#include "message_queue.hpp"

SHELL_CMD_REGISTER(sub_motor, NULL, "Toggle LED", toggle_device_led);


static int cmd_motor_move(const struct shell *sh, size_t argc, char **argv)
{
    int ret = 0;

    // shell_print(sh, "argc = %d", argc);
    if (argc < 2)
    {
        shell_print(sh, "Must enter a direction \"Forward\" or \"Backward\"");
        ret = -1;
    }

    return 0;
}

static int cmd_motor_set_speed(const struct shell *sh, size_t argc, char **argv)
{
    int ret = 0;

    if (argc < 2)
    {
        shell_print(sh, "Must enter a speed between 0 and 100");
        ret = -1;
    }
    else
    {
        int speed = atoi(argv[1]);
        if(speed < 0 || speed > 100)
        {
            shell_print(sh, "Speed must be between 0 and 100");
            ret = -1;
        }
        else
        {
            shell_print(sh, "Good val");
        //     // mqg_q;
        }
    }

    return ret;
}

static int cmd_motor_sleep(const struct shell *sh, size_t argc, char **argv)
{

    shell_print(sh, "Motor set to IDLE");
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_motor,
                               SHELL_CMD(move, NULL, "Enter \"Forward\" or \"Backward\"", cmd_motor_move),
                               SHELL_CMD(set_speed, NULL, "set PWM% (0-100)", cmd_motor_set_speed),
                               SHELL_CMD(sleep, NULL, "Puts motor in idle state", cmd_motor_sleep),
                               SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(motor, &sub_motor, "Motor Control Commands:", NULL);

