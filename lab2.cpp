#include <iostream>

#include "libs/Person.hpp"
#include "libs/t_m_event.hpp"
#include "libs/Money.hpp"
#include "libs/Time_t.hpp"

using namespace std;

int main()
{
    Person test("Jon", "Smith");
    test.add_money(Money(10000));
    cout << test << endl;
    test.add_event(refill_event(Money(15000), Time_t(-1, -1, 15)));
    test.add_event(refill_event(Money(25000), Time_t(-1, -1, 25)));
    test.add_event(spending_event(Money(700), Time_t(-1, -1, 28)));
    test.add_event(spending_event(Money(400), Time_t(-1, -1, 10)));
    test.add_event(spending_event(Money(500), Time_t()));
    test.add_event(spending_event(Money(2000), Time_t(-1, -1, 26)));
    for (int i = 0; i < 30; i++)
    {
        test.execute_events(Time_t(23, 17, i, 10, 2020));
        cout << "Day " << i << " total: " << test.get_money() << endl;
    }
}