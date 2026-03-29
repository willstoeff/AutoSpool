/**
 * @file message_queue.cpp
 * @brief 
 *
 *
 * @author William Stoeffhaas
 * @date 3/28/26
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "message_queue.hpp"
#include "motor.hpp"

LOG_MODULE_REGISTER(msgq);

static constexpr uint8_t MOTOR_MSGQ_SIZE_MAX = 10;

struct k_msgq motor_msgq;


char motor_msgq_buffer[10 * sizeof(struct motor_msg_t)];

int message_queue_init()
{
    int ret = 0;
    LOG_INF("Message Queue Init");
    k_msgq_init(&motor_msgq, motor_msgq_buffer, sizeof(struct motor_msg_t), MOTOR_MSGQ_SIZE_MAX);
    return ret;
 }