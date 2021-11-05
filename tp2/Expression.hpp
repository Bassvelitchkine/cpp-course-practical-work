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
    virtual ~Expression(){};
    virtual void affiche(std::ostream &out) const = 0;

private:
};

inline std::ostream &operator<<(std::ostream &out, const Expression &e)
{
    e.affiche(out);
    return out;
};

class Nombre : public Expression
{
public:
    Nombre(double val) : val_{val} {}

    void affiche(std::ostream &out) const
    {
        out << val_ << "\n";
    }

private:
    double val_;
};

class Variable : public Expression
{
public:
    Variable(std::string nom) : nom_{nom} {};

    void affiche(std::ostream &out) const
    {
        out << nom_ << "\n";
    };

private:
    std::string nom_;
};

#endif
