#ifndef __TCOMPLEJO__
#define __TCOMPLEJO__

#include <iostream>

using namespace std;

class TComplejo
{

    friend ostream &operator<<(ostream &, TComplejo &);
    friend TComplejo operator+(double, const TComplejo &);
    friend TComplejo operator-(double, const TComplejo &);
    friend TComplejo operator*(double, const TComplejo &);

private:
    double re;

    double im;

public:
    TComplejo(double = 0, double = 0);
    TComplejo(const TComplejo &);
    ~TComplejo();
    TComplejo &operator=(const TComplejo &);

    double Re();
    double Im();

    void Re(double);
    void Im(double);

    double Arg(void);
    double Mod(void);

    TComplejo operator+(const TComplejo &);
    TComplejo operator-(const TComplejo &);
    TComplejo operator*(const TComplejo &);
    TComplejo operator+(double);
    TComplejo operator-(double);
    TComplejo operator*(double);
    bool operator==(const TComplejo &);
    bool operator!=(const TComplejo &);
};

#endif