/**
 * @file shell.cpp
 * @brief 
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
    motor_msg_t msg;
    char buffer[9] = {};
    
    if (argc < 2)
    {
        shell_print(sh, "Must enter a direction \"Forward\" or \"Backward\"");
        ret = -1;
    }
    else
    {
        snprintf(buffer, sizeof(buffer), "%s", argv[1]);
        if (!strcmp(buffer, "Forward"))
        {
            msg.data_type = MOTOR_MOVE;
            msg.data = 0;
        }
        else if(!strcmp(buffer, "Backward"))
        {
            msg.data_type = MOTOR_MOVE;
            msg.data = 1;
        }
        else
        {
            shell_print(sh, "Invalid Direction: %s", argv[1]);
            ret = -1;
        }

        if (!ret)
        {
            k_msgq_put(&motor_msgq, &msg, K_NO_WAIT);
        }
    }
    shell_print(sh, "str: %s", argv[1]);
    return ret;
}

static int cmd_motor_set_speed(const struct shell *sh, size_t argc, char **argv)
{
    int ret = 0;
    motor_msg_t msg;

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
            msg.data_type = MOTOR_SPEED;
            msg.data = speed;
            k_msgq_put(&motor_msgq, &msg, K_NO_WAIT);
        }
    }

    return ret;
}

static int cmd_motor_sleep(const struct shell *sh, size_t argc, char **argv)
{
    int ret = 0;
    motor_msg_t msg;

    msg.data_type = MOTOR_SLEEP; 
    msg.data = 1; 

    k_msgq_put(&motor_msgq, &msg, K_NO_WAIT);
    shell_print(sh, "Motor set to IDLE");
    return ret;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_motor,
                               SHELL_CMD(move, NULL, "Enter \"Forward\" or \"Backward\"", cmd_motor_move),
                               SHELL_CMD(set_speed, NULL, "set PWM% (0-100)", cmd_motor_set_speed),
                               SHELL_CMD(sleep, NULL, "Puts motor in idle state", cmd_motor_sleep),
                               SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(motor, &sub_motor, "Motor Control Commands:", NULL);

