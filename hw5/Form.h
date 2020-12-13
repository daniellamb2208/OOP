#ifndef __Form_H__
#define __Form_H__

#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

struct smanip;
class Form
{
public:
    explicit Form(int p) : precisions(p) { ff = ios_base::fmtflags(); }
    ~Form() = default;

    smanip operator()(double v); //take value of being output

    Form &scientific()
    {
        ff |= cout.scientific;
        return *this;
    }
    Form &fixed()
    {
        ff |= cout.fixed;
        return *this;
    }
    Form &precision(int p)
    {
        precisions = p;
        return *this;
    }

    inline ios_base::fmtflags get_flags() { return ff; }
    inline int get_precision() { return precisions; }

private:
    int precisions;
    //cppreference.com
    ios_base::fmtflags ff;
    friend ostream &operator<<(ostream &, smanip &);
};

struct smanip
{
    Form f;
    double v;
    smanip(Form &ff, double vv) : f(ff), v(vv) {}
};
smanip Form::operator()(double v)
{
    return smanip(*this, v);
}

ostream &operator<<(ostream &o, smanip m) //replace &m
{
    stringstream ss;           //resolve default output error, which is influenced by settting flags
    ss.flags(m.f.get_flags()); //m(struct).f(Form).ff(fmtflags)
    ss.precision(m.f.get_precision());
    ss << m.v;
    o << ss.str();
    return o;
}
#endif