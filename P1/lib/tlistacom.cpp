#include "tlistacom.h"

// IMPLEMENTACIÓN TLISTANODO

TListaNodo::TListaNodo() : e(), anterior(nullptr), siguiente(nullptr) {}

TListaNodo::TListaNodo(const TListaNodo &otro) : e(otro.e), anterior(nullptr), siguiente(nullptr) {}

TListaNodo::~TListaNodo()
{
    e.~TComplejo();
    anterior = nullptr;
    siguiente = nullptr;
}

TListaNodo &TListaNodo::operator=(const TListaNodo &otro)
{
    if (this != &otro)
    {
        e = otro.e;
    }
    return *this;
}

// IMPLEMENTACIÓN TLISTAPOS

TListaPos::TListaPos() : pos(nullptr) {}

TListaPos::TListaPos(const TListaPos &otra) : pos(otra.pos) {}

TListaPos::~TListaPos()
{
    pos = nullptr;
}

TListaPos &TListaPos::operator=(const TListaPos &otra)
{
    if (this != &otra)
    {
        pos = otra.pos;
    }
    return *this;
}

bool TListaPos::operator==(const TListaPos &otra) const
{
    return pos == otra.pos;
}

bool TListaPos::operator!=(const TListaPos &otra) const
{
    return pos != otra.pos;
}

TListaPos TListaPos::Anterior() const
{
    TListaPos p;
    if (pos != nullptr)
    {
        p.pos = pos->anterior;
    }
    return p;
}

TListaPos TListaPos::Siguiente() const
{
    TListaPos p;
    if (pos != nullptr)
    {
        p.pos = pos->siguiente;
    }
    return p;
}

bool TListaPos::EsVacia() const
{
    return pos == nullptr;
}

// IMPLEMENTACIÓN TLISTACOM

TListaCom::TListaCom() : primero(nullptr), ultimo(nullptr) {}

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

TListaCom &TListaCom::operator=(const TListaCom &otra)
{
    if (this != &otra)
    {
        this->~TListaCom();

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

bool TListaCom::operator!=(const TListaCom &otra) const
{
    return !(*this == otra);
}

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

TListaCom TListaCom::operator-(const TListaCom &otra) const
{
    TListaCom nueva;
    TListaPos p = Primera();

    while (!p.EsVacia())
    {
        TComplejo elem = Obtener(p);

        if (!otra.Buscar(elem))
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

bool TListaCom::EsVacia() const
{
    return primero == nullptr;
}

bool TListaCom::InsCabeza(const TComplejo &e)
{
    TListaNodo *nuevo = new TListaNodo();
    if (nuevo == nullptr)
    {
        return false;
    }

    nuevo->e = e;
    if (EsVacia())
    {
        primero = nuevo;
        ultimo = nuevo;
    }
    else
    {
        nuevo->siguiente = primero;
        primero->anterior = nuevo;
        primero = nuevo;
    }
    return true;
}

bool TListaCom::InsertarI(const TComplejo &e, const TListaPos &p)
{
    if (p.EsVacia())
    {
        return false;
    }

    if (p.pos == primero)
    {
        return InsCabeza(e);
    }

    TListaNodo *nuevo = new TListaNodo();
    if (nuevo == nullptr)
    {
        return false;
    }
    nuevo->e = e;

    nuevo->siguiente = p.pos;
    nuevo->anterior = p.pos->anterior;
    p.pos->anterior->siguiente = nuevo;
    p.pos->anterior = nuevo;

    return true;
}

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

    nuevo->anterior = p.pos;
    nuevo->siguiente = p.pos->siguiente;
    p.pos->siguiente = nuevo;

    if (nuevo->siguiente != nullptr)
    {
        nuevo->siguiente->anterior = nuevo;
    }
    else
    {
        ultimo = nuevo;
    }

    return true;
}

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

bool TListaCom::BorrarTodos(const TComplejo &e)
{
    bool borrado_algoritmo = false;
    TListaPos p = Primera();

    while (!p.EsVacia())
    {
        TListaPos siguiente = p.Siguiente();
        if (Obtener(p) == e)
        {
            Borrar(p);
            borrado_algoritmo = true;
        }
        p = siguiente;
    }
    return borrado_algoritmo;
}

bool TListaCom::Borrar(TListaPos &p)
{
    if (p.EsVacia())
    {
        return false;
    }

    TListaNodo *borrar = p.pos;

    if (borrar == primero)
    {
        primero = borrar->siguiente;
    }

    if (borrar == ultimo)
    {
        ultimo = borrar->anterior;
    }

    if (borrar->anterior != nullptr)
    {
        borrar->anterior->siguiente = borrar->siguiente;
    }

    if (borrar->siguiente != nullptr)
    {
        borrar->siguiente->anterior = borrar->anterior;
    }

    delete borrar;

    p.pos = nullptr;

    return true;
}

TComplejo TListaCom::Obtener(const TListaPos &p) const
{
    if (p.EsVacia())
    {
        return TComplejo();
    }
    return p.pos->e;
}

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

TListaPos TListaCom::Primera() const
{
    TListaPos p;
    p.pos = primero;
    return p;
}

TListaPos TListaCom::Ultima() const
{
    TListaPos p;
    p.pos = ultimo;
    return p;
}

ostream &operator<<(ostream &os, const TListaCom &lista)
{
    os << "{";
    TListaPos p = lista.Primera();
    while (!p.EsVacia())
    {
        os << lista.Obtener(p);
        p = p.Siguiente();
        if (!p.EsVacia())
        {
            os << " ";
        }
    }
    os << "}";
    return os;
}