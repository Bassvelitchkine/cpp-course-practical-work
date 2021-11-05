/*
 * Cursus CentraleSupélec - Dominante Mathématiques et Data Sciences
 * 3MD1080 - C++ - TP n°2
 *
 * Expression.hpp
 */

#ifndef EXPRESSION_HPP_INCLUDED
#define EXPRESSION_HPP_INCLUDED

#include <iostream>
#include <string>
#include <utility>
#include <memory>

class Expression
{
public:
    // TODO
private:
};

class Nombre : public Expression
{
public:
    Nombre(double val) : val_{val} {}

private:
    double val_;
};

class Variable : public Expression
{
public:
    Variable(std::string nom) : nom_{nom} {};

private:
    std::string nom_;
}

#endif
