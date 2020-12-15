#include "host.hpp"
#include <iostream>

host::host(double power) : avalible_power(power)
{
}

host::~host()
{
}

const char *host::Device_names(d_types type) //костыль для вывода
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

std::vector<size_t> host::path_to_adress(std::string path)
{
    size_t pos = 0;
    std::vector<size_t> temp;
    while ((pos = path.find("-")) != std::string::npos)
    {
        temp.push_back(std::stoull(path.substr(0, pos)));
        path.erase(0, pos + 1);
    }
    temp.push_back(std::stoull(path));
    return temp;
}

std::shared_ptr<Base_device> host::get_device(std::vector<size_t> adress) const //not working with empty address
{
    const Hub *hub = &root_hub;
    for (size_t i = 0; i < adress.size() - 1; i++)
    {
        hub = (Hub *)hub->get_device(adress[i]).get();
    }
    return hub->get_device(adress[adress.size() - 1]);
}

void host::devices_list() const
{
    std::cout << "Device list" << std::endl;
    std::cout << "path" << ' ' << "type"
              << " "
              << "is_active" << std::endl;
    hub_printing(root_hub);
}

void host::hub_printing(const Hub &taget_hub, const std::string prefix) const
{
    auto list = taget_hub.get_device_list();
    for (size_t i = 0; i < list.size(); i++)
    {
        std::cout << prefix << i << " " << Device_names(list[i]) << " " << taget_hub.is_device_active(i) << std::endl;
        if (list[i] == hub)
        {
            hub_printing(*((Hub *)taget_hub.get_device(i).get()), std::to_string(i) + "-");
        }
    }
}

void host::add_device(std::string path, Base_device *new_device)
{
    if (path == "")
    {
        root_hub.connect_device(new_device);
    }
    else
    {
        auto adress = path_to_adress(path);
        auto taget_hub = get_device(adress);
        ((Hub *)taget_hub.get())->connect_device(new_device);
    }
}

bool host::switch_power(std::string path)
{
    if (path == "")
        return false;
    auto adress = path_to_adress(path);
    auto taget_device = get_device(adress);
    Hub *taget_hub;
    if (adress.size() == 1)
    {
        taget_hub = &root_hub;
    }
    else
    {
        auto copy_adress = adress;
        auto it = copy_adress.begin();
        for (size_t i = 0; i < copy_adress.size() - 1; i++)
        {
            it++;
        }
        copy_adress.erase(it);
        taget_hub = (Hub *)get_device(copy_adress).get();
    }

    if (taget_hub->is_device_active(adress[adress.size() - 1]))
    {
        taget_hub->switch_device(adress[adress.size() - 1]);
        return true;
    }
    else
    {
        if (taget_device->get_consumption() + root_hub.get_consumption() < avalible_power)
        {
            taget_hub->switch_device(adress[adress.size() - 1]);
            return true;
        }
    }
    return false;
}

bool host::remove_device(std::string path)
{
    if (path == "")
    {
        return false;
    }
    auto adress = path_to_adress(path);
    if (adress.size() == 1)
    {
        if (adress[0] >= root_hub.get_device_list().size())
        {
            return false;
        }
        root_hub.remove_device(adress[0]);
        return true;
    }
    Hub *taget_hub;
    {
        auto copy_adress = adress;
        auto it = copy_adress.begin();
        for (size_t i = 0; i < copy_adress.size() - 1; i++)
        {
            it++;
        }
        copy_adress.erase(it);
        taget_hub = (Hub *)get_device(copy_adress).get();
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

void host::print_power() const
{
    std::cout << "Common power " << root_hub.get_consumption() << "/" << avalible_power << std::endl;
}