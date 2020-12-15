#ifndef BASE_H
#define BASE_H
#include "device_types.hpp"

class Base_device
{
private:
    double power;
    d_types type;

public:
    Base_device(d_types type, double consumption = 0);
    d_types get_type() const;
    virtual double get_consumption() const;
    ~Base_device();
};

#endif