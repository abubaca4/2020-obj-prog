#include "Money.hpp"

std::ostream &operator<<(std::ostream &os, const Money &t)
{
    return os << t.get_rub() << ',' << int(t.get_cop());
}

Money Money::operator+(const Money &rv) const
{
    int znak = this->rub * rv.get_rub() >= 0 ? 1 : -1;
    if (znak == 1)
    {
        return Money((this->rub < 0 ? -1 : 1) * abs(abs(this->rub) + abs(rv.get_rub()) + (this->cop + rv.get_cop()) / 100),
                     (this->cop + rv.get_cop()) % 100);
    }
    else
    {
        const Money *big, *small;
        if (abs(this->rub) < abs(rv.get_rub()))
        {
            big = &rv;
            small = this;
        }
        else
        {
            big = this;
            small = &rv;
        }
        return Money((big->get_rub() < 0 ? -1 : 1) * (abs(big->get_rub()) - (abs(small->get_rub()) + (small->get_cop() > big->get_cop() ? 1 : 0))),
                     big->get_cop() - small->get_cop() + (small->get_cop() > big->get_cop() ? 100 : 0));
    }
}

Money Money::operator-(const Money &rv) const
{
    return *this + (rv * -1);
}

Money Money::operator*(const int64_t count) const
{
    return Money((count >= 0 ? 1 : -1 * this->rub >= 0 ? 1 : -1) * (abs((this->cop * count) / 100) + abs(count * this->rub)),
                 abs((this->cop * count) % 100));
}

Money Money::operator/(const int64_t count) const
{
    return Money(this->rub / count,
                 (abs(this->rub % count) * 10 + this->cop) / abs(count));
}

bool Money::operator>(const Money &rv) const
{
    return (this->rub > rv.get_rub() || ((this->rub == rv.get_rub()) && (this->cop > rv.get_cop())));
}

bool Money::operator<(const Money &rv) const
{
    return rv > *this;
}

bool Money::operator==(const Money &rv) const
{
    return ((this->rub == rv.get_rub()) && (this->cop == rv.get_cop()));
}

bool Money::operator!=(const Money &rv) const
{
    return !(*this == rv);
}