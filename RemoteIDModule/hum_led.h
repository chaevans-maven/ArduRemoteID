#pragma once

#include <stdint.h>
#include "board_config.h"

#ifdef HUM_LED_PIN
#include <Adafruit_NeoPixel.h>
#endif

class HumLed {
public:
    int led1[3];
    int led2[3];
    int led3[3];
    int led4[3];
    int led5[3];

    void set_state(char self_id[23]) {
        led1[0] = self_id[0];
        led1[1] = self_id[1];
        led1[2] = self_id[2];
        led2[0] = self_id[3];
        led2[1] = self_id[4];
        led2[2] = self_id[5];
        led3[0] = self_id[6];
        led3[1] = self_id[7];
        led3[2] = self_id[8];
        led4[0] = self_id[9];
        led4[1] = self_id[10];
        led4[2] = self_id[11];
        led5[0] = self_id[12];
        led5[1] = self_id[13];
        led5[2] = self_id[14];
    }

    void update(void);

private:
    void init(void);
    bool done_init;
    uint32_t last_led_trig_ms;

#ifdef HUM_LED_PIN
    uint32_t last_led_strip_ms;
    Adafruit_NeoPixel ledStrip{1, HUM_LED_PIN}; //the BlueMark db210pro boards has two LEDs, therefore we need to use 2.
#endif
};

extern HumLed humLed;
