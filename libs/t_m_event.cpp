#include "t_m_event.hpp"

t_m_event::t_m_event(const Time_t &init) : condition(init)
{
}

bool t_m_event::check(const Time_t &taget) const
{
    bool is_valide_minutes = this->condition.minutes == -1 || this->condition.minutes == taget.minutes;
    bool is_valide_hour = this->condition.hour == -1 || this->condition.hour == taget.hour;
    bool is_valide_day = this->condition.day == -1 || this->condition.day == taget.day;
    bool is_valide_month = this->condition.month == -1 || this->condition.month == taget.month;
    bool is_valide_year = this->condition.year == -1 || this->condition.year == taget.year;
    return is_valide_minutes && is_valide_hour && is_valide_day && is_valide_month && is_valide_year;
}

spending_event::spending_event(const Money &action_sum, const Time_t &init = Time_t()) : t_m_event(init), action_m(action_sum)
{
}

void spending_event::action(Money &taget) const
{
    taget = taget - action_m;
}

refill_event::refill_event(const Money &action_sum, const Time_t &init = Time_t()) : t_m_event(init), action_m(action_sum)
{
}

void refill_event::action(Money &taget) const
{
    taget = taget + action_m;
}