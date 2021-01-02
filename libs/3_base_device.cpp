#include "3_base_device.hpp"

base_device::base_device(const device_types type, const double consumption) : type(type), power(consumption)
{
    stored_signal = new base_signal(base_signal::no_signals);
}

base_device::~base_device()
{
}

const base_device::device_types base_device::get_type() const
{
    return type;
}

const base_signal &base_device::get_signal() const
{
    return *stored_signal;
}

void base_device::send_signal(const base_signal &input_signal)
{
    switch (input_signal.get_type())
    {
    case base_signal::get_power:
        delete stored_signal;
        stored_signal = new power_data_signal(get_consumption());
        break;

    default:
        break;
    }
}

const char *base_device::Device_names(const base_device::device_types type) //костыль для вывода
{
    switch (type)
    {
    case mouse:
        return "mouse";
        break;

    case printer:
        return "printer";
        break;

    case scaner:
        return "scaner";
        break;

    case hub:
        return "hub";
        break;

    default:
        return "unknown device";
        break;
    }
}

const double base_device::get_consumption() const
{
    return power;
}