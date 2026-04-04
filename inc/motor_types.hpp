/**
 * @file motor_types.hpp
 * @brief Motor types
 * 
 * Contains shared enums for motor types
 *
 * @author William Stoeffhaas
 * @date 4/4/26
 */

#pragma once

enum Motor_Direction: uint8_t
{
    MOTOR_FORWARD = 0x00,
    MOTOR_BACKWARD,
    MOTOR_DIRECTION_ERROR
};

enum Motor_State: uint8_t
{
    MOTOR_IDLE = 0x00,
    MOTOR_STOPPED,
    MOTOR_MOVING,
    MOTOR_UNKNOWN
};