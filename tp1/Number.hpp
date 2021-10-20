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
        std::cout << "Number::Number : " << l << "\n";
    }

    ~Number()
    {
        delete first_;
    };

    void print(std::ostream &out) const
    { /* TODO */
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
            std::cout << "Digit::Digit : " << l << "\n";
        }
        // Then a destructor for the structure
        ~Digit()
        {
            if (next_)
            {
                delete next_;
            }
            std::cout << "Digit::~Digit : " << digit_ << "\n";
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

#endif
