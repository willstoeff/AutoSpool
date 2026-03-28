/**
 * @file heartbeat.cpp
 * @brief Setup thread for heatrbeat LED
 *
 * Create and start a thread to toggle a heartbeat LED
 *
 * @author William Stoeffhaas
 * @date 3/28/26
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "gpio.hpp"

LOG_MODULE_REGISTER(heartbeat);

static constexpr uint32_t HEARTBEAT_THREAD_STACK_SIZE = 500;
static constexpr uint8_t HEARTBEAT_THREAD_PRIORITY = 5;
static constexpr uint32_t HEARTBEAT_DELAY_MS = 300;

K_THREAD_STACK_DEFINE(heartbeat_stack_area, HEARTBEAT_THREAD_STACK_SIZE);
struct k_thread heartbeat_thread;

static void heartbeat_entry(void*, void*, void*)
{
	for(;;)
	{
		if (toggle_device_led())
		{
			LOG_ERR("Heartbeat error");
		}
		k_sleep(K_MSEC(HEARTBEAT_DELAY_MS));
	}
}

void heartbeat_init()
{
    LOG_INF("Starting Heartbeat");
    k_tid_t heartbeat_tid = k_thread_create(&heartbeat_thread, heartbeat_stack_area, K_THREAD_STACK_SIZEOF(heartbeat_stack_area),
                                            heartbeat_entry, NULL, NULL, NULL,
                                            HEARTBEAT_THREAD_PRIORITY, 0, K_NO_WAIT);
}