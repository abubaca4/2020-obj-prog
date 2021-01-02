#ifndef hub_H
#define hub_H
#include "3_base_device.hpp"
#include <vector>
#include <memory>

class hub : public base_device
{
protected:
    const double get_consumption() const override;
    bool switch_device(size_t id);
    bool is_device_active(size_t id) const;

private:
    std::vector<std::shared_ptr<base_device>> devices;
    std::vector<bool> is_active;

public:
    hub(double consumption = 0);
    ~hub();
    std::vector<device_types> get_device_list() const;
    std::shared_ptr<base_device> get_device(size_t id) const;
    virtual void send_signal(const base_signal &input_signal) override;
    void connect_device(base_device *new_device);
    bool remove_device(size_t id);
};

#endif