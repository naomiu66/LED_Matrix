#ifndef EFFECT_SNOW_H
#define EFFECT_SNOW_H

#include <EffectBase.h>

struct SnowFlake {
    uint8_t x;
    uint8_t y;
    uint8_t speed;
    CRGB color;
    bool active;
};

class EffectSnow : public EffectBase {

public:
    void init() override;

    void update(CRGB *leds) override;

private:
    static const uint8_t MAX_SNOWFLAKES = 50;
    SnowFlake _snowFlakes[MAX_SNOWFLAKES];
    unsigned long _lastFrameTime = 0;
    const uint16_t _frameDelay = 33;
    uint16_t _snowChance = 5;

    void spawnSnowFlake();
    void updateSnowFlakes();
    void drawSnowFlakes(CRGB *leds);
};

#endif