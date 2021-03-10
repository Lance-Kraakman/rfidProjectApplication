#include "sdkconfig.h"

#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "../components/Processing/inputProcessing/inputProcessor.h"
#include "../components/Processing/displayProcessing/displayProcessor.h"
#include "lvgl.h"

void createApplication(void *arg);

void app_main(void)
{

	vTaskDelay(500/portTICK_RATE_MS);
	xTaskCreate(createApplication, "createApplication", 4096, NULL, 1, NULL);

	startInputProcessor();
	startDisplayProcessor();

}

void createApplication(void *arg) {
	while(1) {
		vTaskDelay(50/portTICK_RATE_MS);
	}
}
