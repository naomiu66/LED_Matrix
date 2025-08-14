#ifndef EFFECT_CONFETTI_H
#define EFFECT_CONFETTI_H

#include <EffectBase.h>

class EffectConfetti : public EffectBase {
public:
    void init() override;

    void update(CRGB *leds) override;

private:
    uint8_t hue;
};

#endif