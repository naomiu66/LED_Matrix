#include "EffectFire.h"

void EffectFire::init() {
    generateLine();
}

void EffectFire::update(CRGB *leds) {
    if(_pcnt >= 100) {
        shiftUp();
        generateLine();
        _pcnt = 0;
    }
    drawFrame(_pcnt, leds);
    _pcnt += _fireSpeed;
}

void EffectFire::shiftUp() {
    for(int16_t y = HEIGHT - 1; y > 0; y--) {
        for(uint16_t x = 0; x < WIDTH; x++) {
            uint8_t val = _matrixValue[y-1][x];

            if(random8(100) < _emberDecay){
                val = 0;
            }

            _matrixValue[y][x] = val;
        }
    }

    for(uint16_t x = 0; x < WIDTH; x++) {
        _matrixValue[0][x] = _line[x];
    }
}

void EffectFire::generateLine()
{
    for(uint16_t x = 0; x < WIDTH; x++) {
        _line[x] = random8(64, 255);
    }
}

void EffectFire::drawFrame(int pcnt, CRGB *leds) {
    int nextv;

    for (uint8_t y = 0; y < HEIGHT; y++) {
        for (uint8_t x = 0; x < WIDTH; x++) {
            uint8_t prevValue = (y == 0) ? _line[x] : _matrixValue[y-1][x];
            uint8_t maskY = min(y, (uint8_t)7);
            nextv = ((100 - pcnt) * _matrixValue[y][x] + pcnt * prevValue) / 100;
            nextv = max(0, nextv - pgm_read_byte(&(valueMask[maskY][x])));

            if (y == HEIGHT-1 && SPARKLES && random(0, _sparkleChance) == 0 && nextv > 0) {
                nextv = random8(180, 255);
            }

            leds[getPixelNumber(x, y)] = CHSV(
                pgm_read_byte(&(hueMask[maskY][x])),
                255,
                (uint8_t)max(0, nextv)
            );
        }
    }
}
