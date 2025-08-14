#ifndef EFFECT_WATER_H
#define EFFECT_WATER_H

#include <EffectBase.h>

class EffectWater : public EffectBase {
public:
    void init() override;

    void update(CRGB *leds) override;
private:
    uint8_t gHue;

    uint16_t XY(uint8_t x, uint8_t y);
};

#endif