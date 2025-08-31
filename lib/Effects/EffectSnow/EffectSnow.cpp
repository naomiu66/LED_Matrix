#include "EffectSnow.h"

void EffectSnow::init() {
    for(int i = 0; i < MAX_SNOWFLAKES; i++) {
        _snowFlakes[i].active = false;
    }
}

void EffectSnow::update(CRGB *leds)
{
    if(random(0, _snowChance) == 0) {
        spawnSnowFlake();
    }

    unsigned long now = millis();

    if(now - _lastFrameTime >= _frameDelay)
    {
        _lastFrameTime = now;
        updateSnowFlakes();
        FastLED.clearData();
        drawSnowFlakes(leds);
    }
}

void EffectSnow::spawnSnowFlake() {
    for(int i = 0; i < MAX_SNOWFLAKES; i++) {
        if(!_snowFlakes[i].active) {
            _snowFlakes[i].x = random8(0, WIDTH);
            _snowFlakes[i].y = HEIGHT;
            _snowFlakes[i].speed = 1;
            _snowFlakes[i].color = 0xE0FFFF - 0x101010 * random(0, 4);
            _snowFlakes[i].active = true;
            break;
        }
    }
}

void EffectSnow::updateSnowFlakes() {
    for(int i = 0; i < MAX_SNOWFLAKES; i++) {
        if(_snowFlakes[i].active) {
            _snowFlakes[i].y -= _snowFlakes[i].speed;

            if(_snowFlakes[i].y > HEIGHT) {
                _snowFlakes[i].active = false;
            }
        }
    }
}

void EffectSnow::drawSnowFlakes(CRGB *leds) {
    for (int i = 0; i < MAX_SNOWFLAKES; i++) {
        if (_snowFlakes[i].active) {
            uint8_t xi = _snowFlakes[i].x;
            uint8_t yi = _snowFlakes[i].y;
            if (xi >= 0 && xi < WIDTH && yi >= 0 && yi < HEIGHT) {
                leds[getPixelNumber(xi, yi)] = _snowFlakes[i].color;
            }
        }
    }
}
