#ifndef CLOCK_H
#define CLOCK_H

#include <DS3231.h>
#include <Wire.h>
#include <array>

class Clock
{
public:
    void init();
    bool isTimeChanged();
    std::array<byte, 3> getTime();
    std::array<byte, 3> getDate();
    byte getDOW();

private:
    byte lastHour = 0, lastMinute = 0, lastDay = 0, lastMonth = 0, lastYear = 0;
    DS3231 rtc; // Create an instance of the DS3231 class

    void setTime(byte hour, byte minute, byte second);
    void setDate(byte year, byte month, byte day);
    void setDOW(byte dow);
};

#endif