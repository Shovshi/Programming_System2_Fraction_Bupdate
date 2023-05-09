#pragma once
#include <iostream>
using namespace std;

namespace ariel
{
    int gcd(int num1, int num2);
    int lcm(int num1, int num2);
    class Fraction
    {

    private:
        int numerator;
        int denominator;

    public:
        // Help functions
        void reduce();

        // Getters and Setters
        int getNumerator() const
        {
            return this->numerator;
        }
        void setNumerator(int numerator)
        {
            this->numerator = numerator;
        }
        void setDenominator(int denominator)
        {
            this->denominator = denominator;
        }
        int getDenominator() const
        {
            return this->denominator;
        }

        // Constructors
        Fraction(int numerator, int denominator);
        Fraction(float num);
        Fraction();

        // Operators
        friend ostream &operator<<(ostream &ostr, const Fraction &frac);
        friend Fraction operator+(const Fraction &frac1, const Fraction &frac2);
        friend Fraction operator-(const Fraction &frac1, const Fraction &frac2);
        friend Fraction operator/(const Fraction &frac1, const Fraction &frac2);
        friend Fraction operator*(const Fraction &frac1, const Fraction &frac2);
        friend Fraction &operator--(Fraction &frac1);
        friend Fraction operator++(Fraction &frac1, int num);
        friend Fraction operator--(Fraction &frac1, int num);
        friend Fraction& operator++(Fraction& frac);
        friend bool operator>(const Fraction &self , const Fraction &other);
        friend bool operator>=(const Fraction &self, const Fraction &other);
        friend bool operator<(const Fraction &self, const Fraction &other);
        friend bool operator<=(const Fraction &self , const Fraction &other);
        friend bool operator==(const Fraction &self , const Fraction &other);
        friend std::istream &operator>>(istream &num, Fraction &frac1);
    };

}
