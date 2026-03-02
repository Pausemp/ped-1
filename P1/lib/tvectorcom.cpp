#include "tvectorcom.h"

TVectorCom::TVectorCom()
{
    c = NULL;
    tamano = 0;
}

TVectorCom::TVectorCom(int t)
{
    if (t <= 0)
    {
        c = NULL;
        tamano = 0;
    }
    else
    {
        tamano = t;
        c = new TComplejo[tamano];
    }
}

TVectorCom::TVectorCom(TVectorCom &v)
{
    tamano = v.tamano;
    if (tamano > 0)
    {
        c = new TComplejo[tamano];
        for (int i = 0; i < tamano; i++)
        {
            c[i] = v.c[i];
        }
    }
    else
    {
        c = NULL;
    }
}

TVectorCom::~TVectorCom()
{
    if (c != NULL)
    {
        delete[] c;
        c = NULL;
    }
    tamano = 0;
}

TVectorCom &TVectorCom::operator=(TVectorCom &v)
{
    if (this != &v)
    {
        if (c != NULL)
        {
            delete[] c;
        }
        tamano = v.tamano;
        if (tamano > 0)
        {
            c = new TComplejo[tamano];
            for (int i = 0; i < tamano; i++)
            {
                c[i] = v.c[i];
            }
        }
        else
        {
            c = NULL;
        }
    }
    return *this;
}

bool TVectorCom::operator==(TVectorCom &v)
{
    if (tamano != v.tamano)
        return false;
    for (int i = 0; i < tamano; i++)
    {
        if (c[i] != v.c[i])
            return false;
    }
    return true;
}

bool TVectorCom::operator!=(TVectorCom &v)
{
    return !(*this == v);
}

TComplejo &TVectorCom::operator[](int i)
{
    if (i >= 1 && i <= tamano)
    {
        return c[i - 1];
    }
    error = TComplejo();
    return error;
}

TComplejo TVectorCom::operator[](int i) const
{
    if (i >= 1 && i <= tamano)
    {
        return c[i - 1];
    }
    return TComplejo();
}

int TVectorCom::Tamano()
{
    return tamano;
}

int TVectorCom::Ocupadas()
{
    int contador = 0;
    TComplejo vacio;
    for (int i = 0; i < tamano; i++)
    {
        if (c[i] != vacio)
        {
            contador++;
        }
    }
    return contador;
}

bool TVectorCom::ExisteCom(TComplejo &com)
{
    for (int i = 0; i < tamano; i++)
    {
        if (c[i] == com)
        {
            return true;
        }
    }
    return false;
}

void TVectorCom::MostrarComplejos(double d)
{
    cout << "[";
    bool primero = true;
    for (int i = 0; i < tamano; i++)
    {
        if (c[i].Re() >= d)
        {
            if (!primero)
            {
                cout << ", ";
            }
            cout << c[i];
            primero = false;
        }
    }
    cout << "]";
}

bool TVectorCom::Redimensionar(int t)
{
    if (t <= 0 || t == tamano)
    {
        return false;
    }

    TComplejo *aux = new TComplejo[t];
    int min_tamano = (t < tamano) ? t : tamano;

    for (int i = 0; i < min_tamano; i++)
    {
        aux[i] = c[i];
    }

    if (c != NULL)
    {
        delete[] c;
    }

    c = aux;
    tamano = t;
    return true;
}

ostream &operator<<(ostream &os, TVectorCom &v)
{
    os << "[";
    for (int i = 0; i < v.tamano; i++)
    {
        os << "(" << i + 1 << ") " << v.c[i];
        if (i < v.tamano - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}