#include "Rational.h"
#include <numeric>

struct Lcm {
public:
    const int lcm;
    const int atl;
    const int btl;
    Lcm(int a, int b) : 
    lcm(std::lcm(a, b)), atl(lcm / a), btl(lcm / b) {}
};


Rational& Rational::operator+=(Rational r) {
    auto lcm = Lcm(n, r.n);
    d *= lcm.atl;
    r.d *= lcm.btl;
    n = lcm.lcm;
    d += r.d;
    MakeBeaty();
    return *this;
}

Rational& Rational::operator-=(Rational r) {
    auto lcm = Lcm(n, r.n);
    d *= lcm.atl;
    r.d *= lcm.btl;
    n = lcm.lcm;
    d -= r.d;
    MakeBeaty();
    return *this;
}

Rational& Rational::operator*=(const Rational& r) {
    d *= r.d;
    n *= r.n;
    MakeBeaty();
    return *this;
}

Rational& Rational::operator/=(const Rational& r) {
    d *= r.n;
    n *= r.d;
    MakeBeaty();
    return *this;
}

Rational::Rational(int d, int n) : d(d), n(n) {

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
    os << r.d << '\\' << r.n;
    return os;
}

bool operator==(const Rational& l, const Rational& r) {
    return l.d == r.d && l.n == r.n;
}\

void Rational::MakeBeaty() {
    int gcd = std::gcd(d, n);
    d /= gcd;
    n /= gcd;
}
double Rational::operator<=>(const Rational& r) const {
    double q = double(*this) - double(r);
    //double q = 0.1;
    double g = double(q);
    return g;
    //return 0.1;
}
