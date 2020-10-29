#include "Person.hpp"

std::ostream &operator<<(std::ostream &os, const Person &t)
{
    return os << t.get_name() << ' ' << t.get_last_name() << ' ' << t.get_money();
}