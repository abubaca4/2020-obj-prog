#ifndef t_m_event_H
#define t_m_event_H

#include "Time_t.hpp"

class t_m_event
{
private:
    Time_t condition;

public:
    t_m_event(const Time_t &init = Time_t());
    bool check(const Time_t &taget) const;
};

#endif