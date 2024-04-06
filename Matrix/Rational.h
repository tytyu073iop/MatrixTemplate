#pragma once
#include <iostream>

class Rational {
    long double d = 0;
public:
    Rational(long double d = 0);
    Rational operator+(const Rational& r) const;
    Rational operator-(const Rational& r) const;
    Rational operator*(const Rational& r) const;
    Rational operator/(const Rational& r) const;
    Rational operator-() const;
    long double operator<=>(const Rational& r) const;
    bool operator==(const Rational& r) const;
    Rational& operator+=(const Rational& r);
    Rational& operator-=(const Rational& r);
    Rational& operator*=(const Rational& r);
    Rational& operator/=(const Rational& r);
    friend std::ostream& operator<<(std::ostream& os, const Rational& r);
};