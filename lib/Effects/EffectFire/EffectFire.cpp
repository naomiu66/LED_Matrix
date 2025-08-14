#include "EffectFire.h"

void EffectFire::init() {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
            heat[i] = 0;
        }
}

void EffectFire::update(CRGB *leds) {
    // Step 1: Cooling
        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            heat[i] = qsub8(heat[i], random8(0, ((55 * 10) / WIDTH) + 2));
        }

        // Step 2: Heat rise
        for (int i = WIDTH * HEIGHT - 1; i >= WIDTH; i--) {
            heat[i] = (heat[i - WIDTH] + heat[i - WIDTH] + heat[i - WIDTH + 1] + heat[i - WIDTH - 1]) / 4;
        }

        // Step 3: Sparking
        if (random8() < 120) {
            int y = random8(WIDTH);
            heat[y] = qadd8(heat[y], random8(160, 255));
        }

        // Step 4: Mapping to colors
        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            leds[i] = HeatColor(heat[i]);
        }
}