#pragma once

#include <stdint.h>
#include "board_config.h"

#ifdef HUM_LED_PIN
#include <Adafruit_NeoPixel.h>
#endif

class HumLed {
public:
    int led[3][3];
    int colorOn;
    int ledOn;
    int onCounterMs;

    void set_state(char self_id[24]) {
        led[0][0] = self_id[10];
        led[0][1] = self_id[11];
        led[0][2] = self_id[12];
        led[1][0] = self_id[13];
        led[1][1] = self_id[14];
        led[1][2] = self_id[15];
        led[2][0] = self_id[16];
        led[2][1] = self_id[17];
        led[2][2] = self_id[18];

        colorOn = 0;
        ledOn = 0;
        onCounterMs = 0;
    }

    void update(void);

private:
    void init(void);
    bool done_init;
    uint32_t last_led_trig_ms;

#ifdef HUM_LED_PIN
    uint32_t last_led_strip_ms;
    Adafruit_NeoPixel ledStrip{4, HUM_LED_PIN, NEO_GRB + NEO_KHZ800}; //the BlueMark db210pro boards has two LEDs, therefore we need to use 2.
#endif
};

extern HumLed humLed;
