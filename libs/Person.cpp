#include "Person.hpp"

std::ostream &operator<<(std::ostream &os, const Person &t)
{
    return os << t.get_name() << ' ' << t.get_last_name() << ' ' << t.get_money();
}

void Person::add_event(t_m_event new_event)
{
    this->events.push_back(std::shared_ptr<t_m_event>(std::move(&new_event)));
}

void Person::execute_events(const Time_t &current_time)
{
    for (auto &i : this->events)
    {
        if (i->check(current_time))
        {
            i->action(this->pouch);
        }
    }
}