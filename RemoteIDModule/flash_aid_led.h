#pragma once

#include <stdint.h>
#include "board_config.h"
#include <Adafruit_NeoPixel.h>

class FlashAidLed {
public:
    void set_state(char self_id[24]) {
        pattern = self_id[20];
        codeCurrent = 0;
        counter = 0;
    }

    void update(void);

private:
    void init(void);
    int pattern; // flash pattern
    int codeCurrent; // current digit of the binary representation of pattern
    int counter; // counter tracking Arduino loop iterations on this flash
    Adafruit_NeoPixel ledStrip{1, AID_LED_FLASH_PIN, NEO_GRB + NEO_KHZ800};
    bool done_init;
};

extern FlashAidLed flashAidLed;
