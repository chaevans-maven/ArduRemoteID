#pragma once

#include <stdint.h>
#include "board_config.h"
#include <Adafruit_NeoPixel.h>

class ColorAidLed {
public:
    void set_state(char self_id[24]) {
        // Extracting the color values from the Self-Id message
        int messageOffset = 10;
        for (int i = 0; i < 9; i++) {
            colors[i / 3][i % 3] = self_id[messageOffset + i];
        }

        color = 0;
        led = 0;
        counter = 0;
    }

    void update(void);
private:
    void init(void);
    int colors[3][3]; // 3x3 array for the 3 colors' RGB values
    int color; // index tracking the current LED color
    int led; // index tracking the current brightest LED
    int counter; // counter tracking Arduino loop iterations on this color
    Adafruit_NeoPixel ledStrip{4, AID_LED_COLOR_PIN, NEO_GRB + NEO_KHZ800};

    bool done_init;
};

extern ColorAidLed colorAidLed;
