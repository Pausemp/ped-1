#include "tlistacom.h"

// IMPLEMENTACIÓN TLISTANODO

// Constructor por defecto
TListaNodo::TListaNodo() : e(), anterior(nullptr), siguiente(nullptr) {}

// Constructoe de copia
TListaNodo::TListaNodo(const TListaNodo &otro) : e(otro.e), anterior(nullptr), siguiente(nullptr) {}

// Destructor
TListaNodo::~TListaNodo()
{
    e.~TComplejo();
    anterior = nullptr;
    siguiente = nullptr;
}

// Operador de asignación
TListaNodo &TListaNodo::operator=(const TListaNodo &otro)
{
    if (this != &otro)
    {
        e = otro.e;
    }
    return *this;
}

// IMPLEMENTACIÓN TLISTAPOS

// Constructor por defecto
TListaPos::TListaPos() : pos(nullptr) {}

// Constructor de copia
TListaPos::TListaPos(const TListaPos &otra) : pos(otra.pos) {}

// Destructor
TListaPos::~TListaPos()
{
    pos = nullptr;
}

// Operador de asignación
TListaPos &TListaPos::operator=(const TListaPos &otra)
{
    if (this != &otra)
    {
        pos = otra.pos;
    }
    return *this;
}

// Comprueba si ambas posiciones apuntan al mismo nodo físico
bool TListaPos::operator==(const TListaPos &otra) const
{
    return pos == otra.pos;
}

// Comprueba si apuntan a nodos distintos
bool TListaPos::operator!=(const TListaPos &otra) const
{
    return pos != otra.pos;
}

// Devuelve la posición del nodo anterior
TListaPos TListaPos::Anterior() const
{
    TListaPos p;
    if (pos != nullptr)
    {
        p.pos = pos->anterior;
    }
    return p;
}

// Devuelve la posición del nodo siguiente
TListaPos TListaPos::Siguiente() const
{
    TListaPos p;
    if (pos != nullptr)
    {
        p.pos = pos->siguiente;
    }
    return p;
}

// Comprueba si la posición es nula
bool TListaPos::EsVacia() const
{
    return pos == nullptr;
}

// IMPLEMENTACIÓN TLISTACOM

// Constructor por defecto
TListaCom::TListaCom() : primero(nullptr), ultimo(nullptr) {}

// Constructor de copia: recorre la lista original y va insertando los elementos
TListaCom::TListaCom(const TListaCom &otra) : primero(nullptr), ultimo(nullptr)
{
    TListaPos p = otra.Primera();
    while (!p.EsVacia())
    {
        if (EsVacia())
        {
            InsCabeza(otra.Obtener(p));
        }
        else
        {
            InsertarD(otra.Obtener(p), Ultima());
        }
        p = p.Siguiente();
    }
}

// Destructor: recorre la lista liberando la memoria de cada nodo
TListaCom::~TListaCom()
{
    TListaNodo *actual = primero;
    while (actual != nullptr)
    {
        TListaNodo *siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    primero = nullptr;
    ultimo = nullptr;
}

// Operador de asignación: vacía la lista actual y copia la nueva
TListaCom &TListaCom::operator=(const TListaCom &otra)
{
    if (this != &otra) // Evita autoasignación
    {
        this->~TListaCom(); // Libera la memoria actual

        TListaPos p = otra.Primera();
        while (!p.EsVacia())
        {
            if (EsVacia())
            {
                InsCabeza(otra.Obtener(p));
            }
            else
            {
                InsertarD(otra.Obtener(p), Ultima());
            }
            p = p.Siguiente();
        }
    }
    return *this;
}

// Operador de igualdad: compara tamaños y luego elemento a elemento
bool TListaCom::operator==(const TListaCom &otra) const
{
    if (Longitud() != otra.Longitud())
    {
        return false;
    }

    TListaPos p1 = Primera();
    TListaPos p2 = otra.Primera();

    while (!p1.EsVacia() && !p2.EsVacia())
    {
        if (Obtener(p1) != otra.Obtener(p2))
        {
            return false;
        }
        p1 = p1.Siguiente();
        p2 = p2.Siguiente();
    }
    return true;
}

// Operador de desigualdad
bool TListaCom::operator!=(const TListaCom &otra) const
{
    return !(*this == otra);
}

// Concatenación +: crea una copia de la lista actual y le añade la segunda
TListaCom TListaCom::operator+(const TListaCom &otra) const
{
    TListaCom nueva(*this);

    TListaPos p = otra.Primera();
    while (!p.EsVacia())
    {
        if (nueva.EsVacia())
        {
            nueva.InsCabeza(otra.Obtener(p));
        }
        else
        {
            nueva.InsertarD(otra.Obtener(p), nueva.Ultima());
        }
        p = p.Siguiente();
    }
    return nueva;
}

// Resta -: elementos de la primera que NO están en la segunda
TListaCom TListaCom::operator-(const TListaCom &otra) const
{
    TListaCom nueva;
    TListaPos p = Primera();

    while (!p.EsVacia())
    {
        TComplejo elem = Obtener(p);

        if (!otra.Buscar(elem)) // Solo inserta si no existe en 'otra'
        {
            if (nueva.EsVacia())
            {
                nueva.InsCabeza(elem);
            }
            else
            {
                nueva.InsertarD(elem, nueva.Ultima());
            }
        }
        p = p.Siguiente();
    }
    return nueva;
}

// Comprueba si la lista está vacía
bool TListaCom::EsVacia() const
{
    return primero == nullptr;
}

// Inserta un nuevo nodo al principio de la lista
bool TListaCom::InsCabeza(const TComplejo &e)
{
    TListaNodo *nuevo = new TListaNodo();
    if (nuevo == nullptr)
    {
        return false; // Fallo al reservar memoria
    }

    nuevo->e = e;
    if (EsVacia()) // Si estaba vacía, el nuevo es el primero y el último
    {
        primero = nuevo;
        ultimo = nuevo;
    }
    else // Si no, se enlaza por la izquierda
    {
        nuevo->siguiente = primero;
        primero->anterior = nuevo;
        primero = nuevo;
    }
    return true;
}

// Inserta un nodo a la izquierda de la posición dada
bool TListaCom::InsertarI(const TComplejo &e, const TListaPos &p)
{
    if (p.EsVacia())
    {
        return false;
    }

    if (p.pos == primero) // Insertar a la izquierda del primero es insertar en cabeza
    {
        return InsCabeza(e);
    }

    TListaNodo *nuevo = new TListaNodo();
    if (nuevo == nullptr)
    {
        return false;
    }
    nuevo->e = e;

    // Ajuste de los 4 punteros
    nuevo->siguiente = p.pos;
    nuevo->anterior = p.pos->anterior;
    p.pos->anterior->siguiente = nuevo;
    p.pos->anterior = nuevo;

    return true;
}

// Inserta un nodo a la derecha de la posición dada
bool TListaCom::InsertarD(const TComplejo &e, const TListaPos &p)
{
    if (p.EsVacia())
    {
        return false;
    }

    TListaNodo *nuevo = new TListaNodo();
    if (nuevo == nullptr)
    {
        return false;
    }
    nuevo->e = e;

    // Ajuste de punteros básicos
    nuevo->anterior = p.pos;
    nuevo->siguiente = p.pos->siguiente;
    p.pos->siguiente = nuevo;

    // Si había un nodo a la derecha, se actualiza su puntero 'anterior'
    if (nuevo->siguiente != nullptr)
    {
        nuevo->siguiente->anterior = nuevo;
    }
    else // Si no, el nuevo nodo es el nuevo último
    {
        ultimo = nuevo;
    }

    return true;
}

// Borra la primera aparición de un elemento
bool TListaCom::Borrar(const TComplejo &e)
{
    TListaPos p = Primera();
    while (!p.EsVacia())
    {
        if (Obtener(p) == e)
        {
            return Borrar(p);
        }
        p = p.Siguiente();
    }
    return false;
}

// Borra todas las apariciones de un elemento
bool TListaCom::BorrarTodos(const TComplejo &e)
{
    bool borrado_algoritmo = false;
    TListaPos p = Primera();

    while (!p.EsVacia())
    {
        TListaPos siguiente = p.Siguiente(); // Guardamos el siguiente antes de borrar 'p'
        if (Obtener(p) == e)
        {
            Borrar(p);
            borrado_algoritmo = true;
        }
        p = siguiente;
    }
    return borrado_algoritmo;
}

// Borra el nodo apuntado por la posición dada e invalida la posición
bool TListaCom::Borrar(TListaPos &p)
{
    if (p.EsVacia())
    {
        return false;
    }

    TListaNodo *borrar = p.pos;

    // Si es el primero, el nuevo primero es el siguiente
    if (borrar == primero)
    {
        primero = borrar->siguiente;
    }

    // Si es el último, el nuevo último es el anterior
    if (borrar == ultimo)
    {
        ultimo = borrar->anterior;
    }

    // Desenlaza el nodo por la izquierda
    if (borrar->anterior != nullptr)
    {
        borrar->anterior->siguiente = borrar->siguiente;
    }

    // Desenlaza el nodo por la derecha
    if (borrar->siguiente != nullptr)
    {
        borrar->siguiente->anterior = borrar->anterior;
    }

    delete borrar; // Libera la memoria

    p.pos = nullptr; // Invalida la posición que se pasó por referencia

    return true;
}

// Devuelve el elemento de la posición dada
TComplejo TListaCom::Obtener(const TListaPos &p) const
{
    if (p.EsVacia())
    {
        return TComplejo();
    }
    return p.pos->e;
}

// Busca si un elemento existe en la lista
bool TListaCom::Buscar(const TComplejo &e) const
{
    TListaPos p = Primera();
    while (!p.EsVacia())
    {
        if (Obtener(p) == e)
        {
            return true;
        }
        p = p.Siguiente();
    }
    return false;
}

// Devuelve el número total de nodos recorriendo la lista
int TListaCom::Longitud() const
{
    int contador = 0;
    TListaPos p = Primera();
    while (!p.EsVacia())
    {
        contador++;
        p = p.Siguiente();
    }
    return contador;
}

// Devuelve una posición apuntando al primer nodo
TListaPos TListaCom::Primera() const
{
    TListaPos p;
    p.pos = primero;
    return p;
}

// Devuelve una posición apuntando al último nodo
TListaPos TListaCom::Ultima() const
{
    TListaPos p;
    p.pos = ultimo;
    return p;
}

// Operador de salida <<: imprime la lista
ostream &operator<<(ostream &os, const TListaCom &lista)
{
    os << "{";
    TListaPos p = lista.Primera();
    while (!p.EsVacia())
    {
        os << lista.Obtener(p);
        p = p.Siguiente();
        if (!p.EsVacia()) // Añade espacio separador salvo en el último elemento
        {
            os << " ";
        }
    }
    os << "}";
    return os;
}