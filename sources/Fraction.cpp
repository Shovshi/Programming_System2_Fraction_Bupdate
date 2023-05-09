#include "Fraction.hpp"
#include <climits>
#include <limits>
namespace ariel
{
    void add_overflow(int num2, int num1)
    {
        int c = num1 + num2;
        if((num1 > 0 && num2>0 && c < 0) || (num1 < 0 && num2 < 0 && c > 0)){
            throw std::overflow_error("Failed");
        }
    }
    void mul_overflow(int num2, int num1){
        int c = num1 * num2;
        if(num1 == 0 || num2 == 0){
            return;
        }
        if(c / num1 != num2){
            throw std::overflow_error("Failed");
        }
    }
    // Help functions
    int gcd(int num1, int num2)
    {
        if (num2 == 0)
            return num1;
        return gcd(num2, num1 % num2);
    }

    int lcm(int num1, int num2)
    {
        return (num1 * num2) / gcd(num1, num2);
    }

    void Fraction::reduce()
    {
        int gcdValue = gcd(this->numerator, this->denominator);

        this->numerator /= gcdValue;
        this->denominator /= gcdValue;
    }

    // Constructors
    Fraction::Fraction(int numerator, int denominator)
    {
        if (denominator == 0)
        {
            throw invalid_argument("Divison by zero is unpossibble");
        }
        if (denominator < 0)
        {
            numerator = numerator * -1;
            denominator = denominator * -1;
        }
        this->numerator = numerator;
        this->denominator = denominator;
        this->reduce();
    }

    Fraction::Fraction(float num)
    {
        // Check if the number is zero
        if (num == 0)
        {
            numerator = 0;
            denominator = 1;
            return;
        }
        this->numerator = num * 1000;
        this->denominator = 1000;
        this->reduce();
    }

    Fraction::Fraction()
    {
        this->numerator = 0;
        this->denominator = 1;
    }

    // Operators Part

    // Operator <<
    std::ostream &operator<<(std::ostream &ostr, const Fraction &frac)
    {
        if (frac.getDenominator() < 0)
        {
            ostr << frac.getNumerator() * -1 << "/" << frac.getDenominator() * -1;
        }
        else
        {
            ostr << frac.getNumerator() << "/" << frac.getDenominator();
        }
        return ostr;
    }

    // Operator >>
    std::istream &operator>>(istream &num, Fraction &frac1)
    {
        int numer, denom;
        if (num >> numer >> denom)
        {
            if (denom == 0)
            {
                throw std::runtime_error("Division by zero is unposibble.");
            }
            else if (denom < 0)
            {
                denom = denom * -1;
                numer = numer * -1;
            }
            frac1.numerator = numer;
            frac1.denominator = denom;
        }
        else
        {
            throw std::runtime_error("Failed");
        }

        return num;
    }

    Fraction operator+(const Fraction &frac1, const Fraction &frac2)
    {        
        int new_den = (frac1.getDenominator()* frac2.getDenominator());
        add_overflow(frac1.getNumerator() * frac2.getDenominator(),
                    (frac2.getNumerator() * frac1.getDenominator()));
        mul_overflow(frac1.getNumerator() , (frac2.getDenominator()));
        mul_overflow(frac2.getNumerator() , (frac1.getDenominator()));
        mul_overflow(frac2.getDenominator() , (frac1.getDenominator()));

        int new_num = (frac1.getNumerator() * frac2.getDenominator()) + (frac2.getNumerator() * frac1.getDenominator());
        Fraction frac = Fraction(new_num, new_den);
        return frac;
    }

    Fraction operator-(const Fraction &frac1, const Fraction &frac2)
    {
        int min_int = std::numeric_limits<int>::min();
        int max_int = std::numeric_limits<int>::min();

        if(frac2.numerator == min_int){
            throw std::overflow_error("Failed");
        }
        return frac1 + Fraction(-1 * frac2.getNumerator(), frac2.getDenominator());
    }

    Fraction operator/(const Fraction &frac1, const Fraction &frac2)
    {
        if (frac2.getNumerator() == 0)
        {
            throw std::runtime_error("Division by zero is unposibble.");
        }

        return frac1 * Fraction(frac2.getDenominator(), frac2.getNumerator());
    }

    Fraction operator*(const Fraction &frac1, const Fraction &frac2)
    {
        cout << frac1<< endl;
        cout << frac2<< endl;
        mul_overflow(frac1.numerator ,frac2.numerator);
        mul_overflow(frac1.denominator ,frac2.denominator);

        int numerator = frac1.numerator * frac2.numerator;
        int denominator = frac1.denominator * frac2.denominator;
        
        Fraction frac = Fraction(numerator, denominator);
        return frac;
    }

    // Postfix ++
    Fraction operator++(Fraction &frac1, int num)
    {
        Fraction oldFraction = Fraction(frac1.getNumerator(), frac1.getDenominator());
        frac1.setNumerator(frac1.getNumerator() + frac1.getDenominator());
        return oldFraction;
    }

    // Postfix --
    Fraction operator--(Fraction &frac1, int num)
    {
        Fraction oldFraction = Fraction(frac1.getNumerator(), frac1.getDenominator());
        frac1.setNumerator(frac1.getNumerator() - frac1.getDenominator());
        return oldFraction;
    }

    // Prefix ++
    Fraction &operator++(Fraction &frac)
    {
        frac = Fraction(frac.getNumerator() + frac.getDenominator(), frac.getDenominator());
        return frac;
    }

    // Prefix --
    Fraction &operator--(Fraction &frac)
    {
        frac = Fraction(frac.getNumerator() - frac.getDenominator(), frac.getDenominator());
        return frac;
    }

    bool operator>(const Fraction &self, const Fraction &other)
    {
        float selfVal = (float)self.getNumerator() / self.getDenominator();
        float otherVal = (float)other.getNumerator() / other.getDenominator();
        return selfVal > otherVal;
    }

    bool operator>=(const Fraction &self, const Fraction &other)
    {
        return ((self > other) || (self == other));
    }

    bool operator<(const Fraction &self, const Fraction &other)
    {
        return other > self;
    }

    bool operator<=(const Fraction &self, const Fraction &other)
    {
        return ((self < other) || (other == self));
    }

    bool operator==(const Fraction &self, const Fraction &other)
    {
        int crossProduct1 = self.getNumerator() * other.getDenominator();
        int crossProduct2 = other.getNumerator() * self.getDenominator();

        // Compare the cross products
        return crossProduct1 == crossProduct2;
    }
}
