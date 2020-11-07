#include "Complex.h"
#include <iostream>
#include <math.h>
using namespace std;

Complex::Complex(const double re, const double im) : real(re), imag(im) {}
Complex::Complex(const Complex &c)
{
    real = c.real;
    imag = c.imag;
}
Complex &Complex::operator=(const Complex &c)
{
    real = c.real;
    imag = c.imag;
    return *this;
}

Complex Complex::Polar(const double leng, const double arg)
{
    real = leng * cos(arg);
    imag = leng * sin(arg);
    return *this;
}

double Complex::Real() { return real; }
double Complex::Imag() { return imag; }
double Complex::Norm() { return real * real + imag * imag; }
double Complex::Abs() { return sqrt(Norm()); }
double Complex::Arg() { return atan2(imag, real); }

Complex Complex::operator++()
{
    real++;
    imag++;
    return *this;
}
Complex Complex::operator++(int)
{
    Complex c = Complex(real, imag);
    real++;
    imag++;
    return c;
}
Complex Complex::operator--()
{
    real--;
    imag--;
    return *this;
}
Complex Complex::operator--(int)
{
    Complex c = Complex(real, imag);
    real--;
    imag--;
    return c;
}

Complex::~Complex() {}

Complex Polar(const double leng, const double arg) { return Complex(leng * cos(arg), leng * sin(arg)); }
double Norm(const Complex &x) { return x.imag * x.imag + x.real * x.real; }
double Abs(const Complex &x) { return sqrt(Norm(x)); }
double Arg(const Complex &x) { return atan2(x.imag, x.real); }
Complex operator+(const Complex &x, const Complex &y) { return Complex(x.real + y.real, x.imag + y.imag); }
Complex operator-(const Complex &x, const Complex &y) { return Complex(x.real - y.real, x.imag - y.imag); }
Complex operator*(const Complex &x, const Complex &y)
{
    //(a,b)(c,d) = (a*c - b*d) + j(a*c + b*d)
    return Complex(x.real * y.real - x.imag * y.imag, x.real * y.imag + y.real * x.imag);
}
Complex operator/(const Complex &x, const Complex &y)
{
    //(a,b)/(c,d) = (a,b)(c,-d)/(c^2+b^2)
    Complex m(y.real, -y.imag);
    m = x * m;
    return Complex(m.real / Norm(y), m.imag / Norm(y));
}
Complex operator+=(Complex &x, const Complex &y)
{
    x = x + y;
    return x;
}
Complex operator-=(Complex &x, const Complex &y)
{
    x = x - y;
    return x;
}
Complex operator*=(Complex &x, const Complex &y)
{
    x = x * y;
    return x;
}
Complex operator/=(Complex &x, const Complex &y)
{
    x = x / y;
    return x;
}
bool operator==(const Complex &x, const Complex &y) { return (x.real == y.real && x.imag == y.imag); }
bool operator!=(const Complex &x, const Complex &y) { return !(x == y); }
ostream &operator<<(ostream &o, const Complex &x)
{
    o << "(" << x.real << "," << x.imag << ")";
    return o;
}