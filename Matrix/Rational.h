#pragma once
#include <iostream>

class Rational {
protected:
    void MakeBeaty();
    int d = 0;
    int n = 0;
public:
    Rational(int d = 0, int n = 1);
    Rational operator+(const Rational& r) const;
    Rational operator-(const Rational& r) const;
    Rational operator*(const Rational& r) const;
    Rational operator/(const Rational& r) const;
    Rational operator-() const;
    double operator<=>(const Rational& r) const;
    bool operator==(const Rational& r) const;
    Rational& operator+=(Rational r);
    Rational& operator-=(Rational r);
    Rational& operator*=(const Rational& r);
    Rational& operator/=(const Rational& r);
    friend std::ostream& operator<<(std::ostream& os, const Rational& r);
    operator double() const {
        return (double)d / n;
    }
};