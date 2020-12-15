#include "Base_device.hpp"

Base_device::Base_device(d_types type, double consumption)
{
    power = consumption;
    this->type = type;
}

Base_device::~Base_device()
{
}

d_types Base_device::get_type() const
{
    return type;
}

double Base_device::get_consumption() const
{
    return power;
}