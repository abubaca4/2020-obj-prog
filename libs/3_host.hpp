#ifndef host_H
#define host_H
#include <memory>
#include <string>
#include <vector>
#include "3_hub.hpp"

class host
{
private:
    double avalible_power;
    hub root_hub;
    void hub_printing(hub &taget_hub, const std::string prefix = "") const;
    std::shared_ptr<base_device> get_device(adress_type adress, size_t limit = 0);

public:
    host(double power);
    ~host();
    void devices_list();
    void add_device(adress_type adress, base_device *new_device); //if string empty root hub
    bool switch_power(adress_type adress);                      //false if not enoth energy
    bool remove_device(adress_type adress);
    void print_power();
    static adress_type path_to_adress(std::string path);
};

#endif