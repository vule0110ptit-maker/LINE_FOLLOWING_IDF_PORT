#ifndef __SENSORS__H
#define __SENSORS__H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_log.h"


void init_hcsr04(void);

float get_distance(void);



#endif