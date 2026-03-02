#ifndef TLISTACOM_H
#define TLISTACOM_H

#include "tcomplejo.h"
#include <iostream>

using namespace std;

// Declaraciones adelantadas para poder definir la amistad
class TListaPos;
class TListaCom;

// =========================================================
// CLASE TLISTANODO
// =========================================================
class TListaNodo
{
    friend class TListaPos;
    friend class TListaCom;

private:
    TComplejo e;           // El elemento del nodo
    TListaNodo *anterior;  // El nodo anterior
    TListaNodo *siguiente; // El nodo siguiente

public:
    // FORMA CANÓNICA
    TListaNodo();
    TListaNodo(const TListaNodo &); // Añadido const por buena práctica
    ~TListaNodo();
    TListaNodo &operator=(const TListaNodo &);
};

// =========================================================
// CLASE TLISTAPOS
// =========================================================
class TListaPos
{
    friend class TListaCom;

private:
    TListaNodo *pos; // Puntero a un nodo de la lista

public:
    // FORMA CANÓNICA
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

// =========================================================
// CLASE TLISTACOM
// =========================================================
class TListaCom
{
    friend ostream &operator<<(ostream &, const TListaCom &);

private:
    TListaNodo *primero; // Primer elemento de la lista
    TListaNodo *ultimo;  // Ultimo elemento de la lista

public:
    // FORMA CANÓNICA
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
    bool Borrar(TListaPos &); // Obligatorio que sea modificado
    TComplejo Obtener(const TListaPos &) const;
    bool Buscar(const TComplejo &) const;
    int Longitud() const;
    TListaPos Primera() const;
    TListaPos Ultima() const;
};

#endif