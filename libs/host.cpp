#include "host.hpp"
#include <iostream>

host::host()
{
    root_hub = std::shared_ptr<Hub>(new Hub);
}

host::~host()
{
}

void host::devices_list() const
{
    hub_printing(root_hub);
}

void host::hub_printing(std::shared_ptr<Hub> taget_hub, std::string prefix) const
{
    auto list = taget_hub->get_device_list();
    std::cout << "Device list" << std::endl;
    std::cout << "path" << ' ' << "type" << std::endl;
    for (size_t i = 0; i < list.size(); i++)
    {
        std::cout << prefix << i << ' ' << list[i] << std::endl;
        if (list[i] == hub)
        {
            hub_printing(std::shared_ptr<Hub>(*taget_hub->get_device(i)), std::to_string(i) + "-");
        }
    }
}