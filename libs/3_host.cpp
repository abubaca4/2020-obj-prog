#include "3_host.hpp"
#include <iostream>

host::host(double power) : avalible_power(power)
{
}

host::~host()
{
}

adress_type host::path_to_adress(std::string path)
{
    size_t pos = 0;
    adress_type temp;
    while ((pos = path.find("-")) != std::string::npos)
    {
        temp.push_back(std::stoull(path.substr(0, pos)));
        path.erase(0, pos + 1);
    }
    temp.push_back(std::stoull(path));
    return temp;
}

std::shared_ptr<base_device> host::get_device(adress_type adress, size_t limit) //not working with empty address
{
    hub *taget_hub = &root_hub;
    size_t taget = limit == 0 ? adress.size() : limit;
    for (size_t i = 0; i < taget - 1; i++)
    {
        taget_hub = (hub *)taget_hub->get_device(adress[i]).get();
    }
    return taget_hub->get_device(adress[taget]);
}

void host::devices_list()
{
    std::cout << "Device list" << std::endl;
    std::cout << "path" << ' ' << "type"
              << " "
              << "is_active" << std::endl;
    hub_printing(root_hub);
}

void host::hub_printing(hub &taget_hub, const std::string prefix) const
{
    auto list = taget_hub.get_device_list();
    for (size_t i = 0; i < list.size(); i++)
    {
        auto signal = base_signal(base_signal::get_state);
        signal.adress = adress_type({i});
        taget_hub.send_signal(signal);
        std::cout << prefix << i << " " << base_device::Device_names(list[i]) << " " << ((state_signal *)&taget_hub.get_signal())->get_state() << std::endl;
        if (list[i] == base_device::hub)
        {
            hub_printing(*((hub *)taget_hub.get_device(i).get()), std::to_string(i) + "-");
        }
    }
}

void host::add_device(adress_type adress, base_device *new_device)
{
    if (adress.size() == 0)
    {
        root_hub.connect_device(new_device);
    }
    else
    {
        auto taget_hub = get_device(adress);
        ((hub *)taget_hub.get())->connect_device(new_device);
    }
}

bool host::switch_power(adress_type adress)
{
    if (adress.size() == 0)
    {
        return false;
    }
    auto taget_device = get_device(adress);
    hub *taget_hub;
    if (adress.size() == 1)
    {
        taget_hub = &root_hub;
    }
    else
    {
        taget_hub = (hub *)get_device(adress, adress.size() - 1).get();
    }
    {
        auto signal = base_signal(base_signal::get_state);
        signal.adress = adress_type({adress[adress.size() - 1]});
        taget_hub->send_signal(signal);
    }
    if (((const state_signal *)&taget_hub->get_signal())->get_state())
    {
        auto signal = base_signal(base_signal::off);
        signal.adress = adress_type({adress[adress.size() - 1]});
        taget_hub->send_signal(signal);
        return true;
    }
    else
    {
        root_hub.send_signal(base_signal(base_signal::get_power));
        auto power_sum = ((const power_data_signal *)&(root_hub.get_signal()))->get_power();
        taget_device->send_signal(base_signal(base_signal::get_power));
        power_sum += ((const power_data_signal *)&(taget_device->get_signal()))->get_power();
        if (power_sum < avalible_power)
        {
            auto signal = base_signal(base_signal::on);
            signal.adress = adress_type({adress[adress.size() - 1]});
            taget_hub->send_signal(signal);
            return true;
        }
    }
    return false;
}

bool host::remove_device(adress_type adress)
{
    if (adress.size() == 0)
    {
        return false;
    }

    hub *taget_hub;
    if (adress.size() == 1)
    {
        taget_hub = &root_hub;
    }
    else
    {
        taget_hub = (hub *)get_device(adress, adress.size() - 1).get();
    }
    if (adress[adress.size() - 1] >= taget_hub->get_device_list().size())
    {
        return false;
    }
    else
    {
        taget_hub->remove_device(adress[adress.size() - 1]);
        return true;
    }
}

void host::print_power()
{
    root_hub.send_signal(base_signal(base_signal::get_power));
    std::cout << "Common power " << ((const power_data_signal *)&(root_hub.get_signal()))->get_power() << "/" << avalible_power << std::endl;
}