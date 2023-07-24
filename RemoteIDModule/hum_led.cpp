#include <Arduino.h>
#include "hum_led.h"
#include "board_config.h"

HumLed humLed;

void HumLed::init(void)
{
    if (done_init) {
        return;
    }
    done_init = true;
#ifdef HUM_LED_PIN
    pinMode(HUM_LED_PIN, OUTPUT);
    ledStrip.begin();
#endif
}

void Led::update(void)
{
    init();

    const uint32_t now_ms = millis();

#ifdef HUM_LED_PIN
    ledStrip.clear();

    ledStrip.setPixelColor(0, ledStrip.Color(128, 0, 0))
    ledStrip.setPixelColor(1, ledStrip.Color(128, 128, 0))
    ledStrip.setPixelColor(2, ledStrip.Color(128, 128, 128))
    ledStrip.setPixelColor(3, ledStrip.Color(128, 0, 128))
    ledStrip.setPixelColor(4, ledStrip.Color(0, 128, 128))


    switch (state) {
    case LedState::ARM_OK:
        ledStrip.setPixelColor(0, ledStrip.Color(0, 255, 0));
        ledStrip.setPixelColor(0, ledStrip.Color(1, 255, 0)); //for db210pro, set the second LED to have the same output (for now)
        break;

    default:
        ledStrip.setPixelColor(0, ledStrip.Color(255, 0, 0));
        ledStrip.setPixelColor(1, ledStrip.Color(255, 0, 0)); //for db210pro, set the second LED to have the same output (for now)
        break;
    }
    if (now_ms - last_led_strip_ms >= 200) {
        last_led_strip_ms = now_ms;
        ledStrip.show();
    }
#endif
}

