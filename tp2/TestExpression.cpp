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

    Expression *nombre = new Nombre(2);
    std::cout << "Expression : " << *nombre << "\n";
    Expression *derived_nombre = nombre->derive("x");
    std::cout << "Derivee : " << *derived_nombre << "\n";

    std::cout << "Nombre d'instances : " << Expression::nb_instances() << "\n"; // Should be 2;

    delete derived_nombre;
    delete nombre;

    Expression *variable = new Variable("x");
    std::cout << "Expression : " << *variable << "\n";
    Expression *derived_variable = variable->derive("x");
    std::cout << "Derivee : " << *derived_variable << "\n";
    delete variable;
    delete derived_variable;
}

void test_addition()
{

    Expression *addition = new Addition(new Nombre(2), new Variable("x"));
    std::cout << "Addition : " << *addition << "\n";

    Expression *derived_addition = addition->derive("x");
    std::cout << "Derivee : " << *derived_addition << "\n";

    delete addition;
    delete derived_addition;
}

void test_multiplication()
{

    Expression *multiplication = new Multiplication(new Nombre(2), new Variable("x"));
    std::cout << "Multiplication : " << *multiplication << "\n";

    Expression *derived_multiplication = multiplication->derive("x");
    std::cout << "Derivee : " << *derived_multiplication << "\n";

    delete multiplication;
    delete derived_multiplication;
}

int main(int argc, char *argv[])
{
    // test12();
    // test_addition();
    test_multiplication();
};