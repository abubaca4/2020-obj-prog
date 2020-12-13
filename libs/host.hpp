#ifndef host_H
#define host_H
#include <memory>
#include <string>
#include "Hub.hpp"

class host
{
private:
    std::shared_ptr<Hub> root_hub;
    void hub_printing(std::shared_ptr<Hub> taget_hub, std::string prefix = "") const;

public:
    host();
    ~host();
    void devices_list() const;
};

#endif