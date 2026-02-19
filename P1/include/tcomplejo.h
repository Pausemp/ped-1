#ifndef __TCOMPLEJO__
#define __TCOMPLEJO__


#include <iostream>

using namespace std;


class TComplejo{

    friend ostream & operator<<(ostream &, TComplejo &);
    friend TComplejo operator+ (double , TComplejo&);
    friend TComplejo operator- (double , TComplejo&);
    friend TComplejo operator* (double , TComplejo&);

    private :

        double re;

        double im;

    public:

        TComplejo(double = 0, double = 0);      
        TComplejo (const TComplejo&);
        ~TComplejo();
        TComplejo& operator= (TComplejo&);

        double Re();
        double Im();

        void Re(double);
        void Im(double);

        double Arg(void);
        double Mod(void);


        TComplejo operator+ (TComplejo&);
        TComplejo operator- (TComplejo&);
        TComplejo operator* (TComplejo&);
        TComplejo operator+ (double);
        TComplejo operator- (double);
        TComplejo operator* (double);
        bool operator== (TComplejo&); 
        bool operator!= (TComplejo&); 



};


#endif