#include "Hub.hpp"

Hub::Hub(double consumption) : Base_device(hub, consumption)
{
}

Hub::~Hub()
{
}

double Hub::get_consumption() const
{
    double sum_power = Base_device::get_consumption();
    for (size_t i = 0; i < devices.size(); i++)
    {
        if (is_active[i])
        {
            sum_power += devices[i]->get_consumption();
        }
    }
    return sum_power;
}

std::vector<d_types> Hub::get_device_list() const
{
    std::vector<d_types> temp(devices.size());
    for (size_t i = 0; i < devices.size(); i++)
    {
        temp[i] = devices[i]->get_type();
    }
    return temp;
}

std::shared_ptr<Base_device> Hub::get_device(size_t id) const
{
    return devices.at(id);
}

bool Hub::is_device_active(size_t id) const
{
    return is_active.at(id);
}

bool Hub::switch_device(size_t id)
{
    is_active[id] = !is_active[id];
    return is_active[id];
}

void Hub::connect_device(Base_device *new_device)
{
    devices.push_back(std::shared_ptr<Base_device>(new_device));
    is_active.push_back(false);
}

bool Hub::remove_device(size_t id)
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