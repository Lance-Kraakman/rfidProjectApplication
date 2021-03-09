/*
 * input_processor.h
 *
 *  Created on: 9/03/2021
 *      Author: lance
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define TAG_IP "INPUT_PROCESSOR_TAG"

#ifndef COMPONENTS_PROCESSING_INPUTPROCESSING_INPUTPROCESSOR_H_
#define COMPONENTS_PROCESSING_INPUTPROCESSING_INPUTPROCESSOR_H_

QueueHandle_t buttonInputQueue;

// Function configures input processor settings
void configInputProcessor();

// Function starts the input processor task
void startInputProcessor();


struct buttonInput {
	int number;
};

struct touchInput {
	int x, y;
};





#endif /* COMPONENTS_PROCESSING_INPUTPROCESSING_INPUT_PROCESSOR_H_ */
