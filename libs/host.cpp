#include "host.hpp"
#include <iostream>

host::host()
{
}

host::~host()
{
}

std::vector<size_t> host::path_to_adress(std::string path)
{
}

void host::devices_list() const
{
    hub_printing(root_hub);
}

void host::hub_printing(const Hub &taget_hub, const std::string prefix) const
{
    auto list = taget_hub.get_device_list();
    std::cout << "Device list" << std::endl;
    std::cout << "path" << ' ' << "type" << std::endl;
    for (size_t i = 0; i < list.size(); i++)
    {
        std::cout << prefix << i << ' ' << list[i] << std::endl;
        if (list[i] == hub)
        {
            hub_printing(*((Hub *)taget_hub.get_device(i).get()), std::to_string(i) + "-");
        }
    }
}