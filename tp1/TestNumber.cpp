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
    delete myNumber;
}

void test31()
{
    Number myNumber{99};
    Number secondNumber{4};
    // Addition
    myNumber.add(7);
    myNumber.print(std::cout);
    std::cout << "\n";
    myNumber.add(3);
    myNumber.print(std::cout);
    std::cout << "\n";
    // Multiplication
    secondNumber.multiply(2);
    secondNumber.print(std::cout);
    std::cout << "\n";
    secondNumber.multiply(5);
    secondNumber.print(std::cout);
    std::cout << "\n";
    secondNumber.multiply(101);
    secondNumber.print(std::cout);
    std::cout << "\n";
}

void test32()
{
    unsigned int n{9};
    factorielle(n).print(std::cout);
}

int main()
{
    test32();
}
