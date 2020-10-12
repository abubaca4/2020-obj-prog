#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Money
{
    int64_t rub;
    uint8_t cop;

public:
    Money(int64_t s_rub = 0, uint8_t s_cop = 0) : rub(s_rub), cop(s_cop) {}
    void set_cop(uint8_t new_cop) { cop = new_cop; }
    void set_rub(int64_t new_rub) { rub = new_rub; }
    const uint8_t get_cop() const { return cop; }
    const int64_t get_rub() const { return rub; }
    friend std::ostream &operator<<(std::ostream &os, const Money &t);
    Money operator+(const Money &rv) const;
    Money operator-(const Money &rv) const;
    Money operator*(const int64_t count) const;
    Money operator/(const int64_t count) const;
    bool operator>(const Money &rv) const;
    bool operator<(const Money &rv) const;
    bool operator==(const Money &rv) const;
    bool operator!=(const Money &rv) const;
};

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

class Person
{
    string name, last_name;
    Money pouch;

public:
    Person(const string& first_name, const string& second_name) : name(first_name), last_name(second_name) {}
    friend std::ostream &operator<<(std::ostream &os, const Person &t);
    const string& get_name() const { return name; }
    const string& get_last_name() const { return last_name; }
    void set_name(const string &new_name) { name = new_name; }
    void set_last_name(const string &new_last_name) { last_name = new_last_name; }
    const Money& get_money() const { return pouch; }
    void decrease_money(const Money &g) { pouch = pouch - g; }
    void add_money(const Money &g) { pouch = pouch + g; }
};

std::ostream &operator<<(std::ostream &os, const Person &t)
{
    return os << t.get_name() << ' ' << t.get_last_name() << ' ' << t.get_money();
}

int main()
{
    cout << Money(11, 50) << endl;
    cout << Money(-11, 50) << endl;
    cout << Money(20, 50) + Money(11, 50) << endl;
    cout << Money(20, 50) + Money(-11, 50) << endl;
    cout << Money(-20, 50) + Money(11, 50) << endl;
    cout << Money(20, 50) - Money(11, 50) << endl;
    cout << Money(20, 50) * 3 << endl;
    cout << Money(20, 50) / 4 << endl;
    cout << (Money(20, 50) > Money(11, 50)) << endl;
    cout << (Money(20, 50) > Money(20, 51)) << endl;
    cout << (Money(20, 50) == Money(20, 50)) << endl;
    Person test("Jon", "Smith");
    cout << test << endl;
    cout << test.get_money() << endl;
    test.add_money(Money(20, 50));
    cout << test << endl;
    test.decrease_money(Money(11, 50));
    cout << test << endl;
}