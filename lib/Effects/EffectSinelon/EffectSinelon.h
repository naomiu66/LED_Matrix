#ifndef EFFECT_SINELON_H
#define EFFECT_SINELON_H

#include <EffectBase.h>

class EffectSinelon : public EffectBase {
public:
    void init() override; // Initialize the effect

    void update(CRGB *leds) override; // Update the effect state
private:
    uint8_t hue;
};

#endif