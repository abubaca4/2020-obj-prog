#ifndef host_H
#define host_H
#include <memory>
#include <string>
#include <vector>
#include "Hub.hpp"

class host
{
private:
    Hub root_hub;
    void hub_printing(const Hub &taget_hub, const std::string prefix = "") const;
    static std::vector<size_t> path_to_adress(std::string path);

public:
    host();
    ~host();
    void devices_list() const;
};

#endif