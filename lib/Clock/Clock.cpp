#include <Clock.h>

void Clock::init() {
    rtc = new DS3231();
    Wire.begin();

    setTime(12, 0, 0);
    setDate(1, 9, 11);
    setDOW(5);
    Serial.println("Clock initialized with default values.");
}

std::array<byte, 3> Clock::getTime()
{
    std::array<byte, 3> time;
    bool h12 = false, PM_time = false;
    time[0] = rtc->getHour(h12, PM_time);
    time[1] = rtc->getMinute();
    time[2] = rtc->getSecond();

    return time;
}

std::array<byte, 3> Clock::getDate()
{
    std::array<byte, 3> date;
    bool Century = false;
    date[0] = rtc->getYear(); // Day of the month
    date[1] = rtc->getMonth(Century); // Month
    date[2] = rtc->getDate();
    return date;
}

byte Clock::getDOW()
{
    return rtc->getDoW();
}

void Clock::setTime(byte hour, byte minute, byte second)
{
    rtc->setHour(hour);
    rtc->setMinute(minute);
    rtc->setSecond(second);
}

void Clock::setDate(byte year, byte month, byte day)
{
    rtc->setYear(year);
    rtc->setMonth(month);
    rtc->setDate(day);
}

void Clock::setDOW(byte dow)
{
    rtc->setDoW(dow);
}
