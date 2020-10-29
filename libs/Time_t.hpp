#ifndef TIME_T_H
#define TIME_T_H

struct Time_t
{
    int minutes; //-1 any
    int hour;
    int day;
    int month;
    int year;
    Time_t(int minutes = -1,
           int hour = -1,
           int day = -1,
           int month = -1,
           int year = -1);
};

#endif