#ifndef CLOCK_H
#define CLOCK_H

#include <DS3231.h>
#include <Wire.h>
#include <array>

class Clock
{
public:
    void init();
    std::array<byte, 3> getTime();
    std::array<byte, 3> getDate();
    byte getDOW();

private:
    DS3231* rtc = nullptr; // Create an instance of the DS3231 class
    void setTime(byte hour, byte minute, byte second);
    void setDate(byte year, byte month, byte day);
    void setDOW(byte dow);
};

#endif