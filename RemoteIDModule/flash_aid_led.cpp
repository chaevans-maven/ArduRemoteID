#include <Arduino.h>
#include "flash_aid_led.h"
#include "board_config.h"

FlashAidLed flashAidLed;

void FlashAidLed::init(void)
{
    if (done_init) {
        return;
    }
    done_init = true;
    pinMode(AID_LED_FLASH_PIN, OUTPUT);
    ledStrip.begin();
}

void FlashAidLed::update(void)
{
    init();

    counter = (counter + 1) % 100;
    // Every 100 timesteps, show the next element in the flash pattern
    if (counter == 0) {
        codeCurrent = (codeCurrent + 1) % 8;
    }

    ledStrip.clear();
    // Infer whether the LED should be on for this bit of the flash pattern with a bitshift
    int ledOn = (pattern >> (7 - codeCurrent)) % 2;
    ledStrip.setPixelColor(0, ledStrip.Color(ledOn * 200, ledOn * 200, ledOn * 200));

    ledStrip.show();
}

