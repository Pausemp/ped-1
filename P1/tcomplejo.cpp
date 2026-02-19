#include "tcomplejo.h"
#include <cmath>

TComplejo ::TComplejo(double r, double i)
{
    re = r;
    im = i;
}

TComplejo ::TComplejo(const TComplejo &c)
{
    re = c.re;
    im = c.im;
}

TComplejo ::~TComplejo()
{
    re = 0;
    im = 0;
}

TComplejo operator+(double d, TComplejo &otro)
{
    TComplejo t(d);
    return t + otro;
}

TComplejo operator-(double d, TComplejo &otro)
{
    TComplejo t(d);
    return t - otro;
}

TComplejo operator*(double d, TComplejo &otro)
{
    TComplejo t(d);
    return t * otro;
}

void TComplejo ::Re(double re)
{
    this->re = re;
}

void TComplejo ::Im(double im)
{
    this->im = im;
}

double TComplejo ::Re()
{
    return this->re;
}

double TComplejo ::Im()
{
    return this->im;
}

double TComplejo ::Mod()
{
    double a = sqrt(pow(re, 2) + pow(im, 2));
    return a;
}

double TComplejo ::Arg()
{
    double a = atan2(im, re);
    return a;
}

TComplejo &TComplejo ::operator=(TComplejo &otro)
{
    this->re = otro.re;
    this->im = otro.im;

    return *this;
}

TComplejo TComplejo ::operator+(double d)
{
    TComplejo t(d);
    return (*this + t);
}

TComplejo TComplejo ::operator-(double d)
{
    TComplejo t(d);
    return (*this - t);
}

TComplejo TComplejo ::operator*(TComplejo &otro)
{
    TComplejo t;

    // Fórmula de multiplicación de complejos: (ac - bd) + (ad + bc)i
    t.re = (this->re * otro.re) - (this->im * otro.im);
    t.im = (this->re * otro.im) + (this->im * otro.re);

    return t;
}

// Posible cambio

TComplejo TComplejo ::operator+(TComplejo &otro)
{
    TComplejo t;

    t.re = this->re + otro.re;
    t.im = this->im + otro.im;
    return t;
}

// Posible cambio

TComplejo TComplejo ::operator-(TComplejo &otro)
{
    TComplejo t;

    t.re = this->re - otro.re;
    t.im = this->im - otro.im;

    return t;
}
// Posible cambio

TComplejo TComplejo ::operator*(TComplejo &otro)
{
    TComplejo t;

    t.re = this->re * otro.re;
    t.im = this->im * otro.im;

    return t;
}

bool TComplejo ::operator==(TComplejo &otro)
{
    if (this->re == otro.re && this->im == otro.im)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool TComplejo ::operator!=(TComplejo &otro)
{
    if (this->re != otro.re || this->im != otro.im)
    {
        return true;
    }
    else
    {
        return false;
    }
}

ostream &operator<<(ostream &os, TComplejo &complejo)
{
    os << "(" << complejo.re << " " << complejo.im << ")";
    return os;
}