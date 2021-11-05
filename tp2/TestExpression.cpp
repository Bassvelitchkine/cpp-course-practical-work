/*
 * Cursus CentraleSupélec - Dominante Mathématiques et Data Sciences
 * 3MD1080 - C++ - TP n°2
 *
 * TestExpression.cpp
 * c++ -std=c++20 -o TestExpression Expression.cpp TestExpression.cpp
 */

#include <iostream>
#include <utility>

#include "Expression.hpp"

void test12()
{
    // Expression *e = new Multiplication(
    //     new Variable("x"),
    //     new Nombre(2));
    // std::cout << "Expression : " << *e << "\n";
    // Expression *d = e->derive("x");
    // std::cout << "Dérivée : " << *d << "\n";
    // delete e;
    // delete d;
    Expression *nombre = new Nombre(2);
    Expression *variable = new Variable("x");
    operator<<(std::cout, *nombre);
    operator<<(std::cout, *variable);
    delete nombre;
    delete variable;
}

int main(int argc, char *argv[])
{
    test12();
};