/*
 * Cursus CentraleSupélec - Dominante Mathématiques et Data Sciences
 * 3MD1080 - C++ - TP n°2
 *
 * TestExpression.cpp
 * c++ -std=c++2a -o TestExpression Expression.cpp TestExpression.cpp
 */

#include <iostream>
#include <utility>

#include "Expression.hpp"

void test_derivation()
{
    using ExpressionPtr = std::shared_ptr<const Expression>;
    using VariablePtr = std::shared_ptr<const Variable>;
    using NombrePtr = std::shared_ptr<const Nombre>;

    NombrePtr nombre{new Nombre(2)};
    std::cout << "Expression : " << *nombre << "\n";
    ExpressionPtr derived_nombre{nombre->derive("x")};
    std::cout << "Derivee : " << *derived_nombre << "\n";

    std::cout << "Nombre d'instances : " << Expression::nb_instances() << "\n"; // Should be 2;

    VariablePtr variable{new Variable("x")};
    std::cout << "Expression : " << *variable << "\n";
    ExpressionPtr derived_variable{variable->derive("x")};
    std::cout << "Derivee : " << *derived_variable << "\n";
}

void test_addition()
{
    using ExpressionPtr = std::shared_ptr<const Expression>;
    using VariablePtr = std::shared_ptr<const Variable>;
    using NombrePtr = std::shared_ptr<const Nombre>;
    using AdditionPtr = std::shared_ptr<const Addition>;
    using MultiplicationPtr = std::shared_ptr<const Multiplication>;

    NombrePtr two{new Nombre(2)};
    VariablePtr x{new Variable("x")};

    AdditionPtr addition{new Addition{two, x}};
    std::cout << "Addition : " << *addition << "\n";

    ExpressionPtr derived_addition{addition->derive("x")};
    std::cout << "Derivee : " << *derived_addition << "\n";
}

void test_multiplication()
{
    using ExpressionPtr = std::shared_ptr<const Expression>;
    using VariablePtr = std::shared_ptr<const Variable>;
    using NombrePtr = std::shared_ptr<const Nombre>;
    using AdditionPtr = std::shared_ptr<const Addition>;
    using MultiplicationPtr = std::shared_ptr<const Multiplication>;

    NombrePtr two{new Nombre{2}};
    NombrePtr four{new Nombre{4}};
    VariablePtr x{new Variable("x")};

    AdditionPtr addition{new Addition{two, x}};
    std::cout << "Addition : " << *addition << "\n";

    MultiplicationPtr multiplication{new Multiplication{four, x->clone()}};
    std::cout << "Multiplication : " << *multiplication << "\n";

    MultiplicationPtr final_expression{new Multiplication{addition, multiplication}};
    std::cout << "Final expression : " << *final_expression << "\n";

    ExpressionPtr derived_expression{final_expression->derive("x")};
    std::cout << "Derivee : " << *derived_expression << "\n";
}

int main(int argc, char *argv[])
{
    // test_derivation();
    // test_addition();
    test_multiplication();
};