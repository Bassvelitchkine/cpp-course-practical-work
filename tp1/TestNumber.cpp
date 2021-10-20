/*
 * Cursus CentraleSupélec - Dominante Mathématiques et Data Sciences
 * 3MD1080 - C++ - TP n°1
 *
 * TestNumber.cpp
 * c++ -std=c++20 -o TestNumber Number.cpp TestNumber.cpp
 */

#include <exception>
#include <sstream>
#include <utility>

#include "Number.hpp"

void test21()
{
    Number *myNumber = new Number(123);
    delete myNumber;
}

void test22()
{
    Number *myNumber = new Number(243);
    std::cout << *myNumber << "\n";
    operator<<(std::cout, *myNumber);
    delete myNumber;
}

int main()
{
    test22();
}
