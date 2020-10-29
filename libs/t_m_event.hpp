#ifndef t_m_event_H
#define t_m_event_H

#include "Time_t.hpp"
#include "Money.hpp"

class t_m_event
{
private:
    Time_t condition;

public:
    t_m_event(const Time_t &init);
    bool check(const Time_t &taget) const;
    virtual void action(Money &taget);
};

class spending_event : public t_m_event
{
private:
    Money action_m;

public:
    spending_event(const Money &action_sum, const Time_t &init);
    void action(Money &taget) const;
};

class refill_event : public t_m_event
{
private:
    Money action_m;

public:
    refill_event(const Money &action_sum, const Time_t &init);
    void action(Money &taget) const;
};

#endif