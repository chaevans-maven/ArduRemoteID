#include <Arduino.h>
#include "color_aid_led.h"
#include "board_config.h"
#include "math.h"

ColorAidLed colorAidLed;

void ColorAidLed::init(void)
{
    if (done_init) {
        return;
    }
    done_init = true;
    pinMode(AID_LED_COLOR_PIN, OUTPUT);
    ledStrip.begin();
}

void ColorAidLed::update(void)
{
    init();

    counter = (counter + 1) % 200;
    if (counter % 50 == 0) {
        led = (led + 1) % 4;
    }
    if (counter == 0) {
        color = (color + 1) % 3;
    }

    ledStrip.clear();
    for (int i = 0; i < 4; i++) {
        int brightnessFactor = pow(2.0, (((led - i) % 4) + 4) % 4);
        ledStrip.setPixelColor(i, ledStrip.Color(colors[color][1] / brightnessFactor, colors[color][0] / brightnessFactor, colors[color][2] / brightnessFactor));
    }

    ledStrip.show();
}

