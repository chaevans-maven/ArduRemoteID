#include <Arduino.h>
#include "hum_led_2.h"
#include "board_config.h"

HumLed2 humLed2;

void HumLed2::init(void)
{
    if (done_init) {
        return;
    }
    done_init = true;
#ifdef HUM_LED_PIN_2
    pinMode(HUM_LED_PIN_2, OUTPUT);
    ledStrip.begin();
#endif
}

void HumLed2::update(void)
{
    init();

    codeCounterMs = (codeCounterMs + 1) % 100;
    if (codeCounterMs == 0) {
        codeCurrent = (codeCurrent + 1) % 8;
    }

    const uint32_t now_ms = millis();



#ifdef HUM_LED_PIN_2
    ledStrip.clear();
    int ledOn = (code >> (7 - codeCurrent)) % 2;
    ledStrip.setPixelColor(0, ledStrip.Color(ledOn * led[0], ledOn * led[1], ledOn * led[2]));

    ledStrip.show();
#endif
}

