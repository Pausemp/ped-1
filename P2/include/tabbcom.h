#ifndef _TABBCOM_H_
#define _TABBCOM_H_

#include "tcomplejo.h"
#include "tvectorcom.h"
#include <iostream>

using namespace std;

class TNodoABB; // Declaración adelantada para poder usarla en TABBCom

class TABBCom {
    friend class TNodoABB;
private:
    // Puntero al nodo
    TNodoABB *nodo;

    // Devuelve el recorrido en inorden
    void InordenAux(TVectorCom &, int &);
    // Devuelve el recorrido en preorden
    void PreordenAux(TVectorCom &, int &);
    // Devuelve el recorrido en postorden
    void PostordenAux(TVectorCom &, int &);

public:
    // FORMA CANÓNICA
    // Constructor por defecto
    TABBCom();
    // Constructor de copia
    TABBCom(TABBCom &);
    // Destructor
    ~TABBCom();
    // Sobrecarga del operador asignación
    TABBCom & operator=(TABBCom &);

    // MÉTODOS
    // Sobrecarga del operador igualdad
    bool operator==(TABBCom &);
    // Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
    bool EsVacio();
    // Inserta el elemento en el árbol
    bool Insertar(TComplejo &);
    // Borra el elemento en el árbol
    bool Borrar(TComplejo &);
    // Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
    bool Buscar(TComplejo &);
    // Devuelve el elemento en la raíz del árbol
    TComplejo Raiz();
    // Devuelve la altura del árbol (la altura de un árbol vacío es 0)
    int Altura();
    // Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
    int Nodos();
    // Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
    int NodosHoja();
    // Devuelve el recorrido en inorden
    TVectorCom Inorden();
    // Devuelve el recorrido en preorden
    TVectorCom Preorden();
    // Devuelve el recorrido en postorden
    TVectorCom Postorden();
    // Devuelve el recorrido en niveles
    TVectorCom Niveles();

    // Sobrecarga del operador salida
    friend ostream & operator<<(ostream &, TABBCom &);
};

class TNodoABB {
    friend class TABBCom;
private:
    // El elemento del nodo
    TComplejo item;
    // Subárbol izquierdo y derecho
    TABBCom iz, de;

public:
    // FORMA CANÓNICA
    // Constructor por defecto
    TNodoABB();
    // Constructor de copia
    TNodoABB(TNodoABB &);
    // Destructor
    ~TNodoABB();
    // Sobrecarga del operador asignación
    TNodoABB & operator=(TNodoABB &);
};

#endif