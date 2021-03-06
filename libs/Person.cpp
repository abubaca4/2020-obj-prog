#include "Person.hpp"

std::ostream &operator<<(std::ostream &os, const Person &t)
{
    return os << t.get_name() << ' ' << t.get_last_name() << ' ' << t.get_money();
}

void Person::add_event(time_money_event *new_event)
{
    this->events.push_back(std::shared_ptr<time_money_event>(new_event));
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