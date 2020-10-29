#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "Money.hpp"
#include "t_m_event.hpp"
#include "Time_t.hpp"

class Person
{
    std::string name, last_name;
    std::vector<std::shared_ptr<t_m_event>> events;
    Money pouch;

public:
    Person(const std::string &first_name, const std::string &second_name) : name(first_name), last_name(second_name) {}
    friend std::ostream &operator<<(std::ostream &os, const Person &t);
    const std::string &get_name() const { return name; }
    const std::string &get_last_name() const { return last_name; }
    void set_name(const std::string &new_name) { name = new_name; }
    void set_last_name(const std::string &new_last_name) { last_name = new_last_name; }
    const Money &get_money() const { return pouch; }
    void decrease_money(const Money &g) { pouch = pouch - g; }
    void add_money(const Money &g) { pouch = pouch + g; }
    void add_event(t_m_event new_event);
    void execute_events(const Time_t &current_time);
};

#endif