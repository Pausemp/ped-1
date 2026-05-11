#include "tvectorcom.h"

// Constructor por defecto
TVectorCom::TVectorCom()
{
    c = NULL;
    tamano = 0;
}

// Constructor con tamaño
TVectorCom::TVectorCom(int t)
{
    if (t <= 0) // Si el tamaño es inválido, crea vector vacío
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

// Constructor de copia
TVectorCom::TVectorCom(const TVectorCom &v)
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

// Destructor
TVectorCom::~TVectorCom()
{
    if (c != NULL)
    {
        delete[] c;
        c = NULL;
    }
    tamano = 0;
}

// Operador de asignación: libera memoria actual, reserva nueva y copia profunda
TVectorCom &TVectorCom::operator=(const TVectorCom &v)
{
    if (this != &v) // Evitar autoasignación
    {
        if (c != NULL)
        {
            delete[] c; // Liberar datos viejos
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

// Comprueba igualdad
bool TVectorCom::operator==(const TVectorCom &v) const
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

// Comprueba desigualdad
bool TVectorCom::operator!=(const TVectorCom &v)
{
    return !(*this == v);
}

// Sobrecarga de []
TComplejo &TVectorCom::operator[](int i)
{
    if (i >= 1 && i <= tamano)
    {
        return c[i - 1]; // Ajuste de índice
    }
    // Si la posición no existe, se devuelve el objeto 'error' limpio
    error = TComplejo();
    return error;
}

// Sobrecarga de []
TComplejo TVectorCom::operator[](int i) const
{
    if (i >= 1 && i <= tamano)
    {
        return c[i - 1];
    }
    // Si la posición no existe, se devuelve un objeto temporal vacío por valor
    return TComplejo();
}

// Devuelve el tamaño
int TVectorCom::Tamano()
{
    return tamano;
}

// Cuenta y devuelve las posiciones que no contienen el complejo
int TVectorCom::Ocupadas()
{
    int contador = 0;
    TComplejo vacio; // Constructor por defecto
    for (int i = 0; i < tamano; i++)
    {
        if (c[i] != vacio)
        {
            contador++;
        }
    }
    return contador;
}

// Busca si un objeto TComplejo específico existe en el vector
bool TVectorCom::ExisteCom(const TComplejo &com)
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

// Imprime complejos cuya parte real sea mayor o igual al parámetro 'd'
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

// Redimensiona el vector
bool TVectorCom::Redimensionar(int t)
{
    if (t <= 0 || t == tamano)
    {
        return false;
    }

    // Crear nuevo array temporal con el nuevo tamaño
    TComplejo *aux = new TComplejo[t];

    // Determinar cuántos elementos hay que copiar (el mínimo entre el tamaño viejo y el nuevo)
    int min_tamano = (t < tamano) ? t : tamano;

    // Copiar datos
    for (int i = 0; i < min_tamano; i++)
    {
        aux[i] = c[i];
    }

    // Liberar la memoria antigua
    if (c != NULL)
    {
        delete[] c;
    }

    // Apuntar al nuevo array y actualizar variable tamaño
    c = aux;
    tamano = t;
    return true;
}

// Sobrecarga de salida <<
ostream &operator<<(ostream &os, const TVectorCom &v)
{
    os << "[";
    for (int i = 0; i < v.tamano; i++)
    {
        os << "(" << i + 1 << ") " << v.c[i]; // El índice visible empieza en 1
        if (i < v.tamano - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}