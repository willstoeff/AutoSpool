/**
 * @file message_queue.hpp
 * @brief Header file for message_queue.cpp
 *
 *
 * @author William Stoeffhaas
 * @date 3/28/26
 */

#pragma once

extern struct k_msgq motor_msgq;

enum Motor_Msg_Data_t: uint8_t
{
    MOTOR_SPEED = 0x00,
    MOTOR_MOVE,
    MOTOR_SLEEP,
    MOTOR_DATA_ERROR
};

struct motor_msg_t
{
    Motor_Msg_Data_t data_type;
    uint32_t data;
};

int message_queue_init();