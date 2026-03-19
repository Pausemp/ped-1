#ifndef TLISTACOM_H
#define TLISTACOM_H

#include "tcomplejo.h"
#include <iostream>

using namespace std;

// Declaraciones previas
class TListaPos;
class TListaCom;

// CLASE TLISTANODO
class TListaNodo
{
    friend class TListaPos;
    friend class TListaCom;

private:
    TComplejo e;
    TListaNodo *anterior;
    TListaNodo *siguiente;

public:
    // Constructores
    TListaNodo();
    TListaNodo(const TListaNodo &);
    ~TListaNodo();

    TListaNodo &operator=(const TListaNodo &);
};

// CLASE TLISTAPOS
class TListaPos
{
    friend class TListaCom;

private:
    TListaNodo *pos; // Puntero a un nodo de la lista

public:
    // Constructores
    TListaPos();
    TListaPos(const TListaPos &);
    ~TListaPos();

    TListaPos &operator=(const TListaPos &);

    // MÉTODOS
    bool operator==(const TListaPos &) const;
    bool operator!=(const TListaPos &) const;
    TListaPos Anterior() const;
    TListaPos Siguiente() const;
    bool EsVacia() const;
};

// CLASE TLISTACOM
class TListaCom
{
    friend ostream &operator<<(ostream &, const TListaCom &);

private:
    TListaNodo *primero;
    TListaNodo *ultimo;

public:
    // Constructores
    TListaCom();
    TListaCom(const TListaCom &);
    ~TListaCom();
    TListaCom &operator=(const TListaCom &);

    // MÉTODOS
    bool operator==(const TListaCom &) const;
    bool operator!=(const TListaCom &) const;
    TListaCom operator+(const TListaCom &) const;
    TListaCom operator-(const TListaCom &) const;

    bool EsVacia() const;
    bool InsCabeza(const TComplejo &);
    bool InsertarI(const TComplejo &, const TListaPos &);
    bool InsertarD(const TComplejo &, const TListaPos &);

    bool Borrar(const TComplejo &);
    bool BorrarTodos(const TComplejo &);
    bool Borrar(TListaPos &);

    TComplejo Obtener(const TListaPos &) const;
    bool Buscar(const TComplejo &) const;
    int Longitud() const;
    TListaPos Primera() const;
    TListaPos Ultima() const;
};

#endif