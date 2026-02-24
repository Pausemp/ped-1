#ifndef TVECTORCOM_H
#define TVECTORCOM_H

#include "tcomplejo.h"
#include <iostream>

using namespace std;

class TVectorCom {
    
    friend ostream & operator<<(ostream&, TVectorCom &);

private:

    TComplejo *c;
    int tamano;
    TComplejo error; 

public:
    
    TVectorCom();
    TVectorCom(int);
    TVectorCom(TVectorCom&);
    ~TVectorCom();
    TVectorCom& operator=(TVectorCom&);

    
    bool operator==(TVectorCom &);
    bool operator!=(TVectorCom &);
    TComplejo & operator[](int);
    TComplejo operator[](int) const;
    int Tamano();
    int Ocupadas();
    bool ExisteCom(TComplejo &);
    void MostrarComplejos(double);
    bool Redimensionar(int);
};

#endif