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
    // Every 50 timesteps, current brightest LED changes to be next in the ring
    if (counter % 50 == 0) {
        led = (led + 1) % 4;
    }
    // Every 200 timesteps, displayed colour changes to next in the pattern
    if (counter == 0) {
        color = (color + 1) % 3;
    }

    ledStrip.clear();
    for (int i = 0; i < 4; i++) {
        // Exponential decay of brightness applied to all LEDs trailing than the current brightest LED
        // This is done to create a pulsating visual effect to draw observer's attention
        int brightnessFactor = pow(2.0, (((led - i) % 4) + 4) % 4);
        ledStrip.setPixelColor(i, ledStrip.Color(colors[color][1] / brightnessFactor, colors[color][0] / brightnessFactor, colors[color][2] / brightnessFactor));
    }

    ledStrip.show();
}

