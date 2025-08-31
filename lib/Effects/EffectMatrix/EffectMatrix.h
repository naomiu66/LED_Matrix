#ifndef EFFECT_MATRIX_H
#define EFFECT_MATRIX_H

#include <EffectBase.h>

class EffectMatrix : EffectBase {

public:
    void init() override;

    void update(CRGB *leds) override;

private:


};

#endif