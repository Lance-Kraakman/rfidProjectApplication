/*
 * input_processor.cpp
 *
 *  Created on: 9/03/2021
 *      Author: lance
 */

#include "inputProcessor.h"

// Static Function Declarations
static void configButtonInputs(gpio_num_t *buttonList, int buttonListLength);
static void pollButtonInputs(void* arg);

// Static Variable Declarations
static xQueueHandle gpioEventQueue = NULL;
static gpio_num_t gpioButtonInputList[] = {GPIO_NUM_25, GPIO_NUM_26};

#define BUTTON_INPUT_LIST_LENGTH 2

xQueueHandle getGpioEventQueue() { // Allows us to get out event queues in other scopes
	return gpioEventQueue;
}

void configInputProcessor() {
	//Configure Buttons and Queues
	gpioEventQueue = xQueueCreate(20, sizeof(uint32_t)); // Configure Event Queue
}

void startInputProcessor() {
	configInputProcessor();
	xTaskCreate(pollButtonInputs, "pollButtonInputs", 4096, NULL, 1, NULL);
}

// Configures inputs
static void configButtonInputs(gpio_num_t *buttonList, int buttonListLength) {

	gpio_config_t io_conf;
	io_conf.intr_type = GPIO_INTR_DISABLE;
	io_conf.mode = GPIO_MODE_INPUT;
	io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
	io_conf.pull_up_en = GPIO_PULLUP_ENABLE;

	// Add pins to GPIO bit mask
	gpio_num_t gpioInputPin;
	uint64_t gpioBitMask = 0;

	for (int i = 0; i < buttonListLength; i++) {
		gpioInputPin =(gpio_num_t) *(buttonList+i);
		gpioBitMask += (1<<gpioInputPin);
	}

	vTaskDelay(50/portTICK_RATE_MS);

	io_conf.pin_bit_mask = gpioBitMask;
	gpio_config(&io_conf);

}

static void pollButtonInputs(void* arg)
{
	// Task Setup
	configButtonInputs(gpioButtonInputList, BUTTON_INPUT_LIST_LENGTH);

    while(1) {

    	// Check for button Inputs
    	for (int i = 0; i < BUTTON_INPUT_LIST_LENGTH; i++) {
    		if (gpio_get_level(gpioButtonInputList[i]) == 0) { // If Button Pressed
    			// Add Button input to queue. Now we need to act on button inputs
    			xQueueSend(gpioEventQueue, &gpioButtonInputList[i], 0);
    			ESP_LOGI(TAG_IP,"Button Pressed: %d",(int) gpioButtonInputList[i]);
    		}
    	}
    	//Task Delay
        vTaskDelay(30/portTICK_RATE_MS);
    }
}



