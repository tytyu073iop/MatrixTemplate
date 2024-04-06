#include "Rational.h"

long double Rational::operator<=>(const Rational& r) const {
    return d - r.d;
}

Rational& Rational::operator+=(const Rational& r) {
    d += r.d;
    return *this;
}

Rational& Rational::operator-=(const Rational& r) {
    d -= r.d;
}

Rational& Rational::operator*=(const Rational& r) {
    d *= r.d;
    return *this;
}

Rational& Rational::operator/=(const Rational& r) {
    d /= r.d;
    return *this;
}

Rational::Rational(long double d) : d(d) {
    
}

Rational Rational::operator+(const Rational& r) const {
    return Rational(*this) += r;
}

Rational Rational::operator-() const {
    return Rational(-d);
}

Rational Rational::operator*(const Rational& r) const {
    return Rational(*this) *= r;
}

Rational Rational::operator/(const Rational& r) const {
    return Rational(*this) /= r;
}

std::ostream &operator<<(std::ostream &os, const Rational &r)
{
    os << r.d;
}

bool Rational::operator==(const Rational& r) const {
    return d == r.d;
}
