#include "3_signals.hpp"

base_signal::base_signal(const signals_type type_of_sig) : type(type_of_sig)
{
    adress = adress_type(0);
}

base_signal::~base_signal()
{
}

const base_signal::signals_type base_signal::get_type() const
{
    return type;
}

power_data_signal::power_data_signal(const double power) : base_signal(base_signal::power_data), power(power)
{
}

power_data_signal::~power_data_signal()
{
}

const double power_data_signal::get_power() const
{
    return power;
}

state_signal::state_signal(const bool state) : base_signal(base_signal::state), state(state)
{
}

state_signal::~state_signal()
{
}

const bool state_signal::get_state() const
{
    return state;
}