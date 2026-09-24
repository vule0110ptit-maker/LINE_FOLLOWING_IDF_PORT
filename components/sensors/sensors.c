#include"sensors.h"

#define TRIG_GPIO  4
#define ECHO_GPIO  5

static const char *TAG = "HCSR-04";

void init_hcsr04(void){
    // cau hinh chan trigger:
    gpio_reset_pin(TRIG_GPIO);
    gpio_set_direction(TRIG_GPIO,GPIO_MODE_OUTPUT);
    gpio_set_level(TRIG_GPIO,0);
    //cau hinh chan echo:
    gpio_reset_pin(ECHO_GPIO);
    gpio_set_direction(ECHO_GPIO,GPIO_MODE_INPUT);

}

float get_distance(void){
    // cau hinh cho trigger cho phan hoi 10us
    gpio_set_level(TRIG_GPIO,0);
    esp_rom_delay_us(10);
    gpio_set_level(TRIG_GPIO,1);
    esp_rom_delay_us(10);
    gpio_set_level(TRIG_GPIO,0);

    //cau hinh chan echo cho xuat muc high 
    int64_t timeout_start = esp_timer_get_time();
    while(gpio_get_level(ECHO_GPIO) == 0){
        if(esp_timer_get_time() - timeout_start > 30000){
            return -1.0f;
        }
    }
    int64_t echo_start = esp_timer_get_time();
    while(gpio_get_level(ECHO_GPIO) == 1){
        if(esp_timer_get_time() - echo_start > 30000){
            return -1.0f;
        }
    }

    int64_t echo_end = esp_timer_get_time();

    int64_t durations = echo_end - echo_start;
    float distance = (durations * 0.0343f) / 2.0f;

    return distance;
}