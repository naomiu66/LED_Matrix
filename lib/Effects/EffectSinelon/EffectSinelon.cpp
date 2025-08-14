#include "EffectSinelon.h"

void EffectSinelon::init() {
    hue = 0;
}

void EffectSinelon::update(CRGB *leds) {
    fadeToBlackBy(leds, WIDTH * HEIGHT, 20);
    int pos = beatsin16(13, 0, WIDTH * HEIGHT - 1);
    leds[pos] += CHSV(hue++, 255, 192);
}
