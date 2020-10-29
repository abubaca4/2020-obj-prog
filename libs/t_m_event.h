#ifndef t_m_event_H
#define t_m_event_H

#include "Time_t.h"

class t_m_event
{
private:
    Time_t condition;

public:
    t_m_event(Time_t init = Time_t());
};

#endif