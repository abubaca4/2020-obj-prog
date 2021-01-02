#include "3_hub.hpp"

hub::hub(double consumption) : base_device(base_device::hub, consumption)
{
}

hub::~hub()
{
}

const double hub::get_consumption() const
{
    double sum_power = base_device::get_consumption();
    for (size_t i = 0; i < devices.size(); i++)
    {
        if (is_active[i])
        {
            devices[i]->send_signal(base_signal(base_signal::get_power));
            if (devices[i]->get_signal().get_type() == base_signal::power_data)
            {
                sum_power += ((const power_data_signal *)&(devices[i]->get_signal()))->get_power();
            }
        }
    }
    return sum_power;
}

std::vector<base_device::device_types> hub::get_device_list() const
{
    std::vector<device_types> temp(devices.size());
    for (size_t i = 0; i < devices.size(); i++)
    {
        temp[i] = devices[i]->get_type();
    }
    return temp;
}

std::shared_ptr<base_device> hub::get_device(size_t id) const
{
    return devices.at(id);
}

bool hub::is_device_active(size_t id) const
{
    return is_active.at(id);
}

bool hub::switch_device(size_t id)
{
    is_active[id] = !is_active[id];
    return is_active[id];
}

void hub::connect_device(base_device *new_device)
{
    devices.push_back(std::shared_ptr<base_device>(new_device));
    is_active.push_back(false);
}

bool hub::remove_device(size_t id)
{
    if (id < devices.size())
    {
        auto t1 = devices.begin();
        auto t2 = is_active.begin();
        for (size_t i = 0; i < id; i++)
        {
            t1++;
            t2++;
        }
        devices.erase(t1);
        is_active.erase(t2);
        return true;
    }
    return false;
}

void hub::send_signal(const base_signal &input_signal)
{
    switch (input_signal.get_type())
    {
    case base_signal::get_power:
        delete stored_signal;
        stored_signal = new power_data_signal(get_consumption());
        break;

    case base_signal::get_state:
        switch (input_signal.adress.size())
        {
        case 1:
            if (input_signal.adress[0] < is_active.size())
            {
                delete stored_signal;
                stored_signal = new state_signal(is_device_active(input_signal.adress[0]));
            }
            else
            {
                delete stored_signal;
                stored_signal = new base_signal(base_signal::no_signals);
            }
            break;

        case 0:
        default:
            break;
        }
        break;

    case base_signal::on:
        if (input_signal.adress[0] < is_active.size() && !is_active[input_signal.adress[0]])
        {
            switch_device(input_signal.adress[0]);
        }
        break;

    case base_signal::off:
        if (input_signal.adress[0] < is_active.size() && is_active[input_signal.adress[0]])
        {
            switch_device(input_signal.adress[0]);
        }
        break;

    default:
        base_device::send_signal(input_signal);
        break;
    }
}