#ifndef t_m_event_H
#define t_m_event_H

#include "Time_t.hpp"
#include "Money.hpp"

class time_money_event
{
private:
    Time_t condition;

public:
    time_money_event(const Time_t &init);
    bool check(const Time_t &taget) const;
    virtual void action(Money &taget) const = 0;
};

class spending_event : public time_money_event
{
private:
    Money action_m;

public:
    spending_event(const Money &action_sum, const Time_t &init);
    void action(Money &taget) const override;
};

class refill_event : public time_money_event
{
private:
    Money action_m;

public:
    refill_event(const Money &action_sum, const Time_t &init);
    void action(Money &taget) const override;
};

#endif