/*
 * Cursus CentraleSupélec - Dominante Mathématiques et Data Sciences
 * 3MD1080 - C++ - TP n°1
 *
 * Number.hpp
 */

#ifndef NUMBER_HPP_INCLUDED
#define NUMBER_HPP_INCLUDED

#include <iostream>
#include <string>
#include <utility>

class Number
{
public:
    Number(unsigned long l) : first_{new Digit{l}}
    {
        //std::cout << "Number::Number : " << l << "\n";
    }

    ~Number()
    {
        delete first_;
    };

    void print(std::ostream &out) const
    {
        this->first_->print(out);
    }

    void add(unsigned int n)
    {
        this->first_->addition(n);
    }

    void multiply(unsigned int n)
    {
        this->first_->multiplication(n, 0);
    }

private:
    using DigitType = unsigned int;
    // Un seul chiffre décimal par maillon : l'objectif ici n'est pas la performance
    static const DigitType number_base{10u};
    struct Digit
    {
        // We first define a constructor for the digit structure
        Digit(unsigned long l)
            : digit_{static_cast<unsigned int>(l % number_base)}, next_{l < number_base ? nullptr : new Digit{l / number_base}}
        {
            //std::cout << "Digit::Digit : " << l << "\n";
        }
        // Then a destructor for the structure
        ~Digit()
        {
            if (next_)
            {
                delete next_;
            }
            //std::cout << "Digit::~Digit : " << digit_ << "\n";
        }
        // A printer for the structure
        void print(std::ostream &out) const
        {
            if (next_)
                this->next_->print(out);
            out << digit_;
        }
        // A few calculations
        void addition(unsigned int n)
        {
            unsigned int temp{this->digit_ + n};
            if (temp < number_base)
            {
                digit_ = temp;
            }
            else
            {
                digit_ = temp % number_base;
                if (next_)
                {
                    next_->addition(temp / number_base);
                }
                else
                {
                    next_ = new Digit(temp / number_base);
                }
            }
        }
        void multiplication(unsigned int n, unsigned int retainer)
        {
            unsigned int temp{this->digit_ * n + retainer};
            digit_ = temp % number_base;
            if (next_)
            {
                next_->multiplication(n, temp / number_base);
            }
            else
            {
                if (temp >= number_base)
                {
                    next_ = new Digit(temp / number_base);
                }
            }
        }
        // Below are the Digit structure attributes
        DigitType digit_;
        Digit *next_;
    };
    Digit *first_;
};

inline std::ostream &operator<<(std::ostream &out, const Number &n)
{
    n.print(out);
    return out;
}

Number factorielle(unsigned int n)
{
    Number myNumber{n};
    if (n == 1 || n == 0 || n == 2)
    {
        return myNumber;
    }
    else
    {
        while (n >= 3)
        {
            n -= 1;
            myNumber.multiply(n);
        }
        return myNumber;
    }
}

#endif
