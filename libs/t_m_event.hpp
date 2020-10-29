#ifndef t_m_event_H
#define t_m_event_H

#include <vector>
#include "Time_t.hpp"
#include "Money.hpp"

class t_m_event
{
private:
    Time_t condition;

public:
    t_m_event(const Time_t &init = Time_t());
    bool check(const Time_t &taget) const;
    virtual bool action();
};

class spending_event : public t_m_event
{
private:
    Money action_m;

public:
    spending_event(const Money &action_sum, const Time_t &init = Time_t());
    bool action(Money &taget) const;
};

#endif