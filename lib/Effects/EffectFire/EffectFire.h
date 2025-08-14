#ifndef EFFECT_FIRE_H
#define EFFECT_FIRE_H

#include <EffectBase.h>

class EffectFire : public EffectBase {
public:
    void init() override;

    void update(CRGB *leds) override;
private:
    uint8_t heat[WIDTH * HEIGHT];
};

#endif