#ifndef hub_H
#define hub_H
#include "Base_device.hpp"
#include "device_types.hpp"
#include <vector>
#include <memory>

class Hub : public Base_device
{
private:
    std::vector<std::shared_ptr<Base_device>> devices;
    std::vector<bool> is_active;

public:
    Hub(double consumption = 0);
    ~Hub();
    double get_consumption() const override;
    std::vector<d_types> get_device_list() const;
    std::shared_ptr<Base_device> get_device(size_t id) const;
    bool is_device_active(size_t id) const;
    bool switch_device(size_t id);
    void connect_device(Base_device *new_device);
    bool remove_device(size_t id);
};

#endif