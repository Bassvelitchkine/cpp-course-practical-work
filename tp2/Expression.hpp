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

// THE MOTHER CLASS: EXPRESSION
class Expression
{
public:
    Expression() { ++nb_instances_; };
    virtual ~Expression() { --nb_instances_; };

    using ExpressionPtr = std::shared_ptr<const Expression>;

    virtual void affiche(std::ostream &out) const = 0;
    virtual ExpressionPtr derive(std::string derivation_variable) const = 0;
    virtual ExpressionPtr clone() const = 0;

    static int nb_instances()
    {
        return nb_instances_;
    }

private:
    static int nb_instances_;
};

inline std::ostream &operator<<(std::ostream &out, const Expression &e)
{
    e.affiche(out);
    return out;
};

// A CHILD CLASS OF EXPRESSION: NOMBRE
class Nombre : public Expression
{
public:
    Nombre(double val) : val_{val} {};
    using NombrePtr = std::shared_ptr<const Nombre>;

    void affiche(std::ostream &out) const
    {
        out << val_;
    };

    ExpressionPtr clone() const
    {
        return NombrePtr{new Nombre{val_}};
    };

    ExpressionPtr derive(std::string derivation_variable) const
    {
        return NombrePtr{new Nombre{0}};
    };

private:
    double val_;
};

// A CHILD CLASS OF EXPRESSION: VARIABLE
class Variable : public Expression
{
public:
    Variable(std::string nom) : nom_{nom} {};
    using NombrePtr = std::shared_ptr<const Nombre>;
    using VariablePtr = std::shared_ptr<const Variable>;

    void affiche(std::ostream &out) const
    {
        out << nom_;
    };

    ExpressionPtr clone() const
    {
        return VariablePtr{new Variable{nom_}};
    };

    ExpressionPtr derive(std::string derivation_variable) const
    {
        return NombrePtr{new Nombre{nom_ == derivation_variable ? 1. : 0.}};
    };

private:
    std::string nom_;
};

class Operation : public Expression
{
public:
    virtual ~Operation(){};
    using OperationPtr = std::shared_ptr<const Operation>;

    virtual ExpressionPtr derive(std::string derivation_variable) const = 0;
    virtual ExpressionPtr clone() const = 0;

    virtual void affiche(std::ostream &out) const = 0;

private:
};

class Addition : public Operation
{
public:
    Addition(ExpressionPtr gauche, ExpressionPtr droite) : gauche_{gauche}, droite_{droite} {};
    using AdditionPtr = std::shared_ptr<const Addition>;

    void affiche(std::ostream &out) const
    {
        out << "(";
        gauche_->affiche(out);
        out << " + ";
        droite_->affiche(out);
        out << ")";
    };

    ExpressionPtr clone() const
    {
        return AdditionPtr{new Addition{gauche_, droite_}};
    };

    ExpressionPtr derive(std::string derivation_variable) const
    {
        ExpressionPtr new_gauche = gauche_->derive(derivation_variable);
        ExpressionPtr new_droite = droite_->derive(derivation_variable);

        return AdditionPtr{new Addition{new_gauche, new_droite}};
    };

private:
    ExpressionPtr gauche_;
    ExpressionPtr droite_;
};

class Multiplication : public Operation
{
public:
    Multiplication(ExpressionPtr gauche, ExpressionPtr droite) : gauche_{gauche}, droite_{droite} {};
    using MultiplicationPtr = std::shared_ptr<const Multiplication>;
    using AdditionPtr = std::shared_ptr<const Addition>;

    void affiche(std::ostream &out) const
    {
        out << "(";
        gauche_->affiche(out);
        out << " * ";
        droite_->affiche(out);
        out << ")";
    };

    ExpressionPtr clone() const
    {
        return MultiplicationPtr{new Multiplication{gauche_, droite_}};
    }

    ExpressionPtr derive(std::string derivation_variable) const
    {
        ExpressionPtr new_gauche{new Multiplication{gauche_->derive(derivation_variable), droite_->clone()}};
        ExpressionPtr new_droite{new Multiplication{gauche_->clone(), droite_->derive(derivation_variable)}};

        return AdditionPtr{new Addition{new_gauche, new_droite}};
    }

private:
    ExpressionPtr gauche_;
    ExpressionPtr droite_;
};

#endif