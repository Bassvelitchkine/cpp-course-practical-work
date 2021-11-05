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

    virtual void affiche(std::ostream &out) const = 0;
    virtual Expression *derive(std::string derivation_variable) const = 0;
    virtual Expression *clone() const = 0;

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

    void affiche(std::ostream &out) const
    {
        out << val_;
    };

    Nombre *clone() const
    {
        return new Nombre{val_};
    };

    Nombre *derive(std::string derivation_variable) const
    {
        return new Nombre{0};
    };

private:
    double val_;
};

// A CHILD CLASS OF EXPRESSION: VARIABLE
class Variable : public Expression
{
public:
    Variable(std::string nom) : nom_{nom} {};

    void affiche(std::ostream &out) const
    {
        out << nom_;
    };

    Variable *clone() const
    {
        return new Variable{nom_};
    };

    Nombre *derive(std::string derivation_variable) const
    {
        return new Nombre{nom_ == derivation_variable ? 1. : 0.};
    };

private:
    std::string nom_;
};

class Operation : public Expression
{
public:
    virtual ~Operation(){};
    virtual Operation *derive(std::string derivation_variable) const = 0;
    virtual void affiche(std::ostream &out) const = 0;
    virtual Operation *clone() const = 0;

private:
};

class Addition : public Operation
{
public:
    Addition(Expression *gauche, Expression *droite) : gauche_{gauche}, droite_{droite} {};

    void affiche(std::ostream &out) const
    {
        out << "(";
        gauche_->affiche(out);
        out << " + ";
        droite_->affiche(out);
        out << ")";
    };

    Addition *clone() const
    {
        return new Addition{gauche_, droite_};
    };

    Addition *derive(std::string derivation_variable) const
    {
        Expression *new_gauche = gauche_->derive(derivation_variable);
        Expression *new_droite = droite_->derive(derivation_variable);

        return new Addition{new_gauche, new_droite};
    };

private:
    Expression *gauche_;
    Expression *droite_;
};

class Multiplication : public Operation
{
public:
    Multiplication(Expression *gauche, Expression *droite) : gauche_{gauche}, droite_{droite} {};

    void affiche(std::ostream &out) const
    {
        out << "(";
        gauche_->affiche(out);
        out << " * ";
        droite_->affiche(out);
        out << ")";
    };

    Multiplication *clone() const
    {
        return new Multiplication{gauche_, droite_};
    }

    Addition *derive(std::string derivation_variable) const
    {
        Expression *new_gauche = new Multiplication{gauche_->derive(derivation_variable), droite_->clone()};
        Expression *new_droite = new Multiplication{gauche_->clone(), droite_->derive(derivation_variable)};

        return new Addition{new_gauche, new_droite};
    }

private:
    Expression *gauche_;
    Expression *droite_;
};

#endif