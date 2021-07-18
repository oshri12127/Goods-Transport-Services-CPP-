//
// Created by Oshri on 19/05/2019.
//

#ifndef HW2_DATEANDTIME_H
#define HW2_DATEANDTIME_H
#include <iostream>
using  namespace std;
class DateAndTime {
public:
    DateAndTime(int day, int month,int hour, int min);
    ~DateAndTime();
    DateAndTime(const DateAndTime&);
    DateAndTime& operator=(const DateAndTime&);
    DateAndTime(DateAndTime&& rhs) = default;
    DateAndTime& operator=(DateAndTime&& rhs)= default;
    int getDay() const;
    int getMonth() const;
    int getMin() const;
    int getHour() const;
    bool operator==(const DateAndTime &rhs) const;
    bool operator<(const DateAndTime &rhs) const;
    bool operator>=(const DateAndTime &rhs) const;

private:
    int day;
    int month;
    int hour;
    int min;

};


#endif //HW2_DATEANDTIME_H
