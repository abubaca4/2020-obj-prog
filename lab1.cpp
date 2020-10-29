#include <iostream>
#include <cmath>
#include <string>

#include "libs/Person.hpp"

using namespace std;

int main()
{
    cout << Money(11, 50) << endl;
    cout << Money(-11, 50) << endl;
    cout << Money(20, 50) + Money(11, 50) << endl;
    cout << Money(20, 50) + Money(-11, 50) << endl;
    cout << Money(-20, 50) + Money(11, 50) << endl;
    cout << Money(20, 50) - Money(11, 50) << endl;
    cout << Money(20, 50) * 3 << endl;
    cout << Money(20, 50) / 4 << endl;
    cout << (Money(20, 50) > Money(11, 50)) << endl;
    cout << (Money(20, 50) > Money(20, 51)) << endl;
    cout << (Money(20, 50) == Money(20, 50)) << endl;
    Person test("Jon", "Smith");
    cout << test << endl;
    cout << test.get_money() << endl;
    test.add_money(Money(20, 50));
    cout << test << endl;
    test.decrease_money(Money(11, 50));
    cout << test << endl;
}