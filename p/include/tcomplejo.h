#ifndef __TCOMPLEJO__
#define __TCOMPLEJO__

#include <iostream>

using namespace std;

class TComplejo
{

    // Funciones amigas para
    friend ostream &operator<<(ostream &, const TComplejo &);
    friend TComplejo operator+(double, const TComplejo &);
    friend TComplejo operator-(double, const TComplejo &);
    friend TComplejo operator*(double, const TComplejo &);

private:
    double re;

    double im;

public:
    // Constructores
    TComplejo(double = 0, double = 0);
    TComplejo(const TComplejo &);
    ~TComplejo();

    TComplejo &operator=(const TComplejo &);

    // Getters
    double Re();
    double Im();

    // Setters
    void Re(double);
    void Im(double);

    double Arg(void);
    double Mod(void);

    // Sobrecarga de operadores complejo
    TComplejo operator+(const TComplejo &);
    TComplejo operator-(const TComplejo &);
    TComplejo operator*(const TComplejo &);

    // Sobrecarga de operadores double
    TComplejo operator+(double);
    TComplejo operator-(double);
    TComplejo operator*(double);

    // Sobrecarga de operadores logicos
    bool operator==(const TComplejo &);
    bool operator!=(const TComplejo &);
};

#endif