#ifndef EFFECT_BASE_H
#define EFFECT_BASE_H

#include <FastLED.h>

class EffectBase {
public:
    virtual void init() = 0; // Initialize the effect
    virtual void update(CRGB *leds) = 0; // Update the effect state
    virtual ~EffectBase() = default; // Virtual destructor for proper cleanup
protected:
    static constexpr uint8_t WIDTH = 16;
    static constexpr uint8_t HEIGHT = 16;
};

#endif