#ifndef TOUCH_H
#define TOUCH_H

#include <Arduino.h>

#pragma pack(push, 1)
typedef struct {        
    bool touch_deb: 1;    
    bool hold_flag: 1;
    bool counter_flag: 1;
    bool isHolded_f: 1;
    bool isRelease_f: 1;
    bool isPress_f: 1;
    bool step_flag: 1;
    bool oneClick_f: 1;
    bool isOne_f: 1;
    bool mode: 1;
    bool counter_reset: 1;            //Добавлен
} TouchFlags;
#pragma pack(pop)

class Touch
{
public:
    void init();

    void setDebounce(uint16_t debounce);
    void setTimeout(uint16_t timeout);
    void setClickTimeout(uint16_t clickTimeout);
    void setStepTimeout(uint16_t stepTimeout);

    boolean isTouch();
    boolean isTouched();
    boolean isReleased();

    boolean isDouble();
    boolean isTriple();

    boolean isHold();
    boolean isHolded();

    boolean hasClicks();
    uint8_t getClicks();
    uint8_t getHoldClicks();

    boolean isStep(byte clicks = 0);

    void update();


    void resetStates();
private:
    static constexpr uint8_t TOUCH_PIN = D5;
    TouchFlags flags;
    uint16_t _debounce = 60;
    uint16_t _timeout = 1000;
    uint16_t _click_timeout = 500;
    uint16_t _step_timeout = 400;
    uint8_t touch_counter = 0, last_counter = 0, last_hold_counter = 0;
    uint32_t touch_timer = 0;    
    bool touch_state = false;
    bool touch_flag = false;
};

#endif