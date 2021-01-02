#ifndef signals_H
#define signals_H
#include <vector>

typedef std::vector<size_t> adress_type;

class base_signal
{
public:
    enum signals_type
    {
        no_signals,
        on,
        off,
        get_power,
        power_data,
        get_state,
        state
    };

private:
    const signals_type type;

public:
    base_signal(const signals_type type_of_sig);
    ~base_signal();
    adress_type adress;
    const signals_type get_type() const;
};

class power_data_signal : public base_signal
{
private:
    const double power;

public:
    power_data_signal(const double power);
    ~power_data_signal();
    const double get_power() const;
};

class state_signal : public base_signal
{
private:
    const bool state;

public:
    state_signal(const bool state);
    ~state_signal();
    const bool get_state() const;
};

#endif