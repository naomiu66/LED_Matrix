#include "EffectConfetti.h"

void EffectConfetti::init() {
    hue = 0;
}

void EffectConfetti::update(CRGB *leds) {
    fadeToBlackBy(leds, WIDTH * HEIGHT, 10);
        int pos = random16(WIDTH * HEIGHT);
        leds[pos] += CHSV(hue + random8(64), 200, 255);
        hue++;
}
