#ifndef MONEY_H
#define MONEY_H

#include <iostream>

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

#endif