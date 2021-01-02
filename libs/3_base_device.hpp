#ifndef BASE_H
#define BASE_H
#include "3_signals.hpp"

class base_device
{
protected:
    base_signal *stored_signal;
    virtual const double get_consumption() const;

public:
    enum device_types
    {
        mouse,
        printer,
        scaner,
        hub
    };
    static const char *Device_names(const base_device::device_types type);

private:
    double power;
    const device_types type;

public:
    base_device(const device_types type, const double consumption = 0);
    ~base_device();
    const device_types get_type() const;
    virtual void send_signal(const base_signal &input_signal);
    const base_signal &get_signal() const;
};

#endif