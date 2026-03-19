#include "tcomplejo.h"
#include <cmath>

// Constructor unificado
TComplejo ::TComplejo(double r, double i)
{
    re = r;
    im = i;
}

// Constructor de copia
TComplejo ::TComplejo(const TComplejo &c)
{
    re = c.re;
    im = c.im;
}

// Destructor
TComplejo ::~TComplejo()
{
    re = 0;
    im = 0;
}

// Función amiga: Sobrecarga de la suma
TComplejo operator+(double d, TComplejo &otro)
{
    TComplejo t(d);
    return t + otro;
}

// Función amiga: Sobrecarga de la resta
TComplejo operator-(double d, TComplejo &otro)
{
    TComplejo t(d);
    return t - otro;
}

// Función amiga: Sobrecarga de la multiplicación
TComplejo operator*(double d, TComplejo &otro)
{
    TComplejo t(d);
    return t * otro;
}

// Setter: Modifica la parte real
void TComplejo ::Re(double re)
{
    this->re = re;
}

// Setter: Modifica la parte imaginaria
void TComplejo ::Im(double im)
{
    this->im = im;
}

// Getter: Devuelve la parte real
double TComplejo ::Re()
{
    return this->re;
}

// Getter: Devuelve la parte imaginaria
double TComplejo ::Im()
{
    return this->im;
}

// Calcula y devuelve el módulo del número complejo
double TComplejo ::Mod()
{
    double a = sqrt(pow(re, 2) + pow(im, 2));
    return a;
}

// Calcula y devuelve el argumento del número complejo
double TComplejo ::Arg()
{
    double a = atan2(im, re);
    return a;
}

// Sobrecarga del operador de asignación
TComplejo &TComplejo ::operator=(const TComplejo &otro)
{
    this->re = otro.re;
    this->im = otro.im;

    return *this;
}

// Sobrecarga de la suma double
TComplejo TComplejo ::operator+(double d)
{
    TComplejo t(d);
    return (*this + t);
}

// Sobrecarga de la resta double
TComplejo TComplejo ::operator-(double d)
{
    TComplejo t(d);
    return (*this - t);
}

// Sobrecarga de la multiplicación double
TComplejo TComplejo ::operator*(double d)
{
    TComplejo t(d);
    return (*this * t);
}

// Sobrecarga de la suma entre dos objetos TComplejo
TComplejo TComplejo ::operator+(const TComplejo &otro)
{
    TComplejo t;

    t.re = this->re + otro.re;
    t.im = this->im + otro.im;
    return t;
}

// Sobrecarga de la resta entre dos objetos TComplejo
TComplejo TComplejo ::operator-(const TComplejo &otro)
{
    TComplejo t;

    t.re = this->re - otro.re;
    t.im = this->im - otro.im;

    return t;
}

// Sobrecarga de la multiplicación entre dos objetos TComplejo
TComplejo TComplejo ::operator*(const TComplejo &otro)
{
    TComplejo t;

    t.re = (this->re * otro.re) - (this->im * otro.im);
    t.im = (this->re * otro.im) + (this->im * otro.re);

    return t;
}

// Operador de igualdad: Comprueba si ambos números tienen misma parte real e imaginaria
bool TComplejo ::operator==(const TComplejo &otro)
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

// Operador de desigualdad: Comprueba si los números son distintos
bool TComplejo ::operator!=(const TComplejo &otro)
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

// Función amiga: Sobrecarga de la salida
ostream &operator<<(ostream &os, const TComplejo &complejo)
{
    os << "(" << complejo.re << " " << complejo.im << ")";
    return os;
}