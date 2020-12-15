#ifndef host_H
#define host_H
#include <memory>
#include <string>
#include <vector>
#include "Hub.hpp"

class host
{
private:
    double avalible_power;
    Hub root_hub;
    void hub_printing(const Hub &taget_hub, const std::string prefix = "") const;
    static std::vector<size_t> path_to_adress(std::string path);
    std::shared_ptr<Base_device> get_device(std::vector<size_t> adress);
    static const char *Device_names(d_types type);

public:
    host(double power);
    ~host();
    void devices_list() const;
    void add_device(std::string path, Base_device *new_device); //if string empty root hub
    bool switch_power(std::string path);                        //false if not enoth energy
    void print_power();
};

#endif