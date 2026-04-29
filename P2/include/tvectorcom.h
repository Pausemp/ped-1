#ifndef TVECTORCOM_H
#define TVECTORCOM_H

#include "tcomplejo.h"
#include <iostream>

using namespace std;

class TVectorCom
{

    // Función amiga: Sobrecarga del operador de salida
    friend ostream &operator<<(ostream &, const TVectorCom &);

private:
    TComplejo *c;
    int tamano;
    TComplejo error;

public:
    // Constructores
    TVectorCom();
    TVectorCom(int);
    TVectorCom(TVectorCom &);
    ~TVectorCom();
    TVectorCom &operator=(TVectorCom &);

    // MÉTODOS Y OPERADORES
    bool operator==(const TVectorCom &) const;
    bool operator!=(const TVectorCom &);

    TComplejo &operator[](int);
    TComplejo operator[](int) const;

    int Tamano();
    int Ocupadas();
    bool ExisteCom(const TComplejo &);
    void MostrarComplejos(double);
    bool Redimensionar(int);
};

#endif