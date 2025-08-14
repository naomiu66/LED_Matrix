#include <EffectWater/EffectWater.h>

void EffectWater::init() {
    gHue = 0;
}

void EffectWater::update(CRGB *leds) {
    gHue++;
        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                uint8_t wave = sin8(x * 8 + gHue) + cos8(y * 8 + gHue);
                leds[XY(x, y)] = CHSV(gHue + wave / 2, 255, wave);
            }
        }
}

uint16_t EffectWater::XY(uint8_t x, uint8_t y) {
    return (y % 2 == 0) ? (y * WIDTH + x) : (y * WIDTH + (WIDTH - 1 - x));
}