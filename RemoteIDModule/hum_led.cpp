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

void HumLed::update(void)
{
    init();

    onCounterMs = (onCounterMs + 1) % 200;

    if (onCounterMs % 50 == 0) {
        ledOn = (ledOn + 1) % 4;
    }
    if (onCounterMs == 0) {
        colorOn = (colorOn + 1) % 3;
    }

    const uint32_t now_ms = millis();

#ifdef HUM_LED_PIN
    ledStrip.clear();
    for (int i = 0; i < 4; i++) {
        if (i == ledOn) {
            ledStrip.setPixelColor(i, ledStrip.Color(led[colorOn][1], led[colorOn][0], led[colorOn][2]));
        } else if ((i + 1) % 4 == ledOn) {
            ledStrip.setPixelColor(i, ledStrip.Color(led[colorOn][1] / 4, led[colorOn][0] / 4, led[colorOn][2] / 4));
        } else if ((i + 2) % 4 == ledOn) {
            ledStrip.setPixelColor(i, ledStrip.Color(led[colorOn][1] / 8, led[colorOn][0] / 8, led[colorOn][2] / 8));
        } else {
            ledStrip.setPixelColor(i, ledStrip.Color(led[colorOn][1] / 16, led[colorOn][0] / 16, led[colorOn][2] / 16));
        }
    }

    ledStrip.show();
#endif
}

