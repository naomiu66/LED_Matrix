#include <Touch.h>

void Touch::init()
{
    pinMode(TOUCH_PIN, INPUT_PULLUP);
    Serial.println("Touch sensor initialized on pin: " + String(TOUCH_PIN));
}

void Touch::setDebounce(uint16_t debounce) {
    _debounce = debounce;
}
void Touch::setTimeout(uint16_t new_timeout) {
    _timeout = new_timeout;
}
void Touch::setClickTimeout(uint16_t new_timeout) {
    _click_timeout = new_timeout;
}
void Touch::setStepTimeout(uint16_t step_timeout) {
    _step_timeout = step_timeout;
}

boolean Touch::isReleased() {
    if (flags.isRelease_f) {
        flags.isRelease_f = false;
        return true;
    } else return false;
}
boolean Touch::isTouch() {    
    if (flags.isOne_f) {
        flags.isOne_f = false;
        return true;
    } else return false;
}
boolean Touch::isHolded() {
    if (flags.isHolded_f) {
        flags.isHolded_f = false;
        return true;
    } else return false;
}
boolean Touch::isHold() {
    if (flags.step_flag) return true;
    else return false;
}
boolean Touch::isTouched() {
    if (flags.counter_flag && last_counter == 1) {
        //        last_counter = 0;
        //        flags.counter_flag = false;
        flags.counter_reset = true;    
        return true;
    } else return false;
}
boolean Touch::isDouble() {
    if (flags.counter_flag && last_counter == 2) {
        //        flags.counter_flag = false;
        //        last_counter = 0;
        flags.counter_reset = true;
        return true;
    } else return false;
}
boolean Touch::isTriple() {
    if (flags.counter_flag && last_counter == 3) {
        //        flags.counter_flag = false;
        //        last_counter = 0;
        flags.counter_reset = true;
        return true;
    } else return false;
}

boolean Touch::hasClicks() {
    if (flags.counter_flag) {
        flags.counter_reset = true;    
        return true;
    } else return false;
}
uint8_t Touch::getClicks() {
    flags.counter_reset = true;    
    return last_counter;
}
uint8_t Touch::getHoldClicks() {
    return last_hold_counter;
}

boolean Touch::isStep(byte clicks) {
    if (touch_counter == clicks && flags.step_flag && (millis() - touch_timer >= _step_timeout)) {
        touch_timer = millis();
        return true;
    }
    else return false;
}

void Touch::resetStates() {
    flags.isPress_f = false;
    flags.isRelease_f = false;
    flags.isOne_f = false;
    flags.isHolded_f = false;
    flags.step_flag = false;
    flags.counter_flag = false;
    last_hold_counter = 0;
    last_counter = 0;
}

void Touch::update()
{    
    // читаем пин
    touch_state = digitalRead(TOUCH_PIN) == HIGH;
    
    uint32_t thisMls = millis();
    
    // нажатие
    if (touch_state && !touch_flag) {
        if (!flags.touch_deb) {
            flags.touch_deb = true;
            touch_timer = thisMls;
        } else {
            if (thisMls - touch_timer >= _debounce) {
                touch_flag = true;            
                flags.isPress_f = true;
                flags.oneClick_f = true;
            }
        }    
    } else {
        flags.touch_deb = false;
    }

    // отпускание
    if (!touch_state && touch_flag) {
        touch_flag = false;
        if (!flags.hold_flag) touch_counter++;
        flags.hold_flag = false;
        flags.isRelease_f = true;
        touch_timer = thisMls;
        if (flags.step_flag) {
            last_counter = 0;
            touch_counter = 0;
            flags.step_flag = false;    
        }        
        if (flags.oneClick_f) {
            flags.oneClick_f = false;
            flags.isOne_f = true;
        }
    }

    // обработка удержания
    if (touch_flag && touch_state && (thisMls - touch_timer >= _timeout) && !flags.hold_flag) {
        flags.hold_flag = true;
        last_hold_counter = touch_counter;
        //btn_counter = 0;
        //last_counter = 0;
        flags.isHolded_f = true;
        flags.step_flag = true;
        flags.oneClick_f = false;
        touch_timer = thisMls;
    }

    // обработка накликивания
    if ((thisMls - touch_timer >= _click_timeout) && (touch_counter != 0) &&  !touch_state) {
        last_counter = touch_counter;
        touch_counter = 0;
        flags.counter_flag = true;
    }
    
    if (flags.counter_reset) {
        last_counter = 0;
        flags.counter_flag = false;
        flags.counter_reset = false;
    }
}


