#include "libs/host.hpp"
#include "libs/Hub.hpp"
#include "libs/Base_device.hpp"
#include "libs/device_types.hpp"

int main()
{
    host test(100);
    test.print_power();
    test.devices_list();
    test.add_device("", new Hub());
    test.add_device("", new Base_device(mouse, 5));
    test.add_device("0", new Base_device(printer, 10));
    test.devices_list();
    test.switch_power("0");
    test.print_power();
}