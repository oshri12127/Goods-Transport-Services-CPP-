//
// Created by Oshri on 19/05/2019.
//

#include "DateAndTime.h"

DateAndTime::~DateAndTime() {

}

DateAndTime::DateAndTime(int day, int month, int hour, int min) : day(day), month(month), hour(hour), min(min) {}

DateAndTime::DateAndTime(const DateAndTime &T) : day(T.day), month(T.month), hour(T.hour), min(T.min) {

}

DateAndTime &DateAndTime::operator=(const DateAndTime &T) {
    if (this == &T)
        return (*this);
    this->day = T.day;
    this->month = T.month;
    this->hour = T.hour;
    this->min = T.min;
    return *this;
}

int DateAndTime::getDay() const {
    return day;
}

int DateAndTime::getMonth() const {
    return month;
}

int DateAndTime::getMin() const {
    return min;
}

int DateAndTime::getHour() const {
    return hour;
}

bool DateAndTime::operator==(const DateAndTime &rhs) const {
    return day == rhs.day &&
           month == rhs.month &&
           min == rhs.min &&
           hour == rhs.hour;
}

bool DateAndTime::operator<(const DateAndTime &rhs) const {
    if (month < rhs.month)
        return true;
    if (rhs.month < month)
        return false;
    if (day < rhs.day && month == rhs.month)
        return true;
    if (rhs.day < day && month == rhs.month)
        return false;
    if (hour < rhs.hour)
        return true;
    if (rhs.hour < hour)
        return false;
    if (min < rhs.min && hour == rhs.hour)
        return true;
    // if (rhs.min < min && hour == rhs.hour)
    return false;
}

bool DateAndTime::operator>=(const DateAndTime &rhs) const {
    return !(*this < rhs);
}






