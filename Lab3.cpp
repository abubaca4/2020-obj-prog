#include "libs/3_host.hpp"
#include "libs/3_hub.hpp"
#include "libs/3_base_device.hpp"

int main()
{
    host test_host(100.0);
    adress_type empty_adress({});
    test_host.add_device(empty_adress, new hub());
    test_host.devices_list();
    test_host.add_device(empty_adress, new base_device(base_device::mouse, 5));
    test_host.devices_list();
    test_host.add_device({0}, new base_device(base_device::printer, 10));
    test_host.devices_list();
    test_host.print_power();
    test_host.switch_power({0});
    test_host.devices_list();
    test_host.switch_power({0, 0});
    test_host.devices_list();
    test_host.print_power();
    test_host.switch_power({1});
    test_host.devices_list();
    test_host.print_power();
    test_host.switch_power({0});
    test_host.devices_list();
    test_host.print_power();
}