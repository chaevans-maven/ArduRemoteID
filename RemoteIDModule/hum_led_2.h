#pragma once

#include <stdint.h>
#include "board_config.h"

#ifdef HUM_LED_PIN_2
#include <Adafruit_NeoPixel.h>
#endif

class HumLed2 {
public:
    int led[3];
    int code;
    int codeCurrent;
    int codeCounterMs;

    void set_state(char self_id[24]) {
        led[0] = 160;
        led[1] = 160;
        led[2] = 160;
        code = self_id[20];

        codeCurrent = 0;
        codeCounterMs = 0;
    }

    void update(void);

private:
    void init(void);
    bool done_init;
    uint32_t last_led_trig_ms;

#ifdef HUM_LED_PIN_2
    uint32_t last_led_strip_ms;
    Adafruit_NeoPixel ledStrip{1, HUM_LED_PIN_2, NEO_GRB + NEO_KHZ800}; //the BlueMark db210pro boards has two LEDs, therefore we need to use 2.
#endif
};

extern HumLed2 humLed2;
