#include "tvectorcom.h"

// Constructor por defecto
TVectorCom::TVectorCom() {
    c = NULL;
    tamano = 0;
}

// Constructor a partir de un tamaño
TVectorCom::TVectorCom(int t) {
    if (t <= 0) {
        c = NULL;
        tamano = 0;
    } else {
        tamano = t;
        c = new TComplejo[tamano];
    }
}

// Constructor de copia
TVectorCom::TVectorCom(TVectorCom &v) {
    tamano = v.tamano;
    if (tamano > 0) {
        c = new TComplejo[tamano];
        for (int i = 0; i < tamano; i++) {
            c[i] = v.c[i];
        }
    } else {
        c = NULL;
    }
}

// Destructor
TVectorCom::~TVectorCom() {
    if (c != NULL) {
        delete[] c;
        c = NULL;
    }
    tamano = 0;
}

// Sobrecarga del operador asignación
TVectorCom & TVectorCom::operator=(TVectorCom &v) {
    if (this != &v) { // Evitar autoasignación
        if (c != NULL) {
            delete[] c;
        }
        tamano = v.tamano;
        if (tamano > 0) {
            c = new TComplejo[tamano];
            for (int i = 0; i < tamano; i++) {
                c[i] = v.c[i];
            }
        } else {
            c = NULL;
        }
    }
    return *this;
}

// Sobrecarga del operador igualdad
bool TVectorCom::operator==(TVectorCom &v) {
    if (tamano != v.tamano) return false;
    for (int i = 0; i < tamano; i++) {
        if (c[i] != v.c[i]) return false;
    }
    return true;
}

// Sobrecarga del operador desigualdad
bool TVectorCom::operator!=(TVectorCom &v) {
    return !(*this == v);
}

// Sobrecarga del operador corchete (parte IZQUIERDA)
TComplejo & TVectorCom::operator[](int i) {
    if (i >= 1 && i <= tamano) {
        return c[i - 1]; // Los arrays en C++ empiezan en 0, pero la lógica del vector exige empezar en 1
    }
    error = TComplejo(); // Devuelve un (0 0) si hay error
    return error;
}

// Sobrecarga del operador corchete (parte DERECHA)
TComplejo TVectorCom::operator[](int i) const {
    if (i >= 1 && i <= tamano) {
        return c[i - 1];
    }
    return TComplejo();
}

// Tamaño del vector
int TVectorCom::Tamano() {
    return tamano;
}

// Cantidad de posiciones OCUPADAS
int TVectorCom::Ocupadas() {
    int contador = 0;
    TComplejo vacio; // Constructor por defecto (0 0)
    for (int i = 0; i < tamano; i++) {
        if (c[i] != vacio) {
            contador++;
        }
    }
    return contador;
}

// Devuelve TRUE si existe el TComplejo
bool TVectorCom::ExisteCom(TComplejo &com) {
    for (int i = 0; i < tamano; i++) {
        if (c[i] == com) {
            return true;
        }
    }
    return false;
}

// Mostrar por pantalla elementos con parte REAL igual o posterior al argumento
void TVectorCom::MostrarComplejos(double d) {
    cout << "[";
    bool primero = true;
    for (int i = 0; i < tamano; i++) {
        if (c[i].Re() >= d) {
            if (!primero) {
                cout << ", ";
            }
            cout << c[i];
            primero = false;
        }
    }
    cout << "]";
}

// Redimensionar el vector
bool TVectorCom::Redimensionar(int t) {
    if (t <= 0 || t == tamano) {
        return false;
    }

    TComplejo *aux = new TComplejo[t];
    int min_tamano = (t < tamano) ? t : tamano;
    
    // Copiar elementos existentes hasta el límite de la nueva dimensión
    for (int i = 0; i < min_tamano; i++) {
        aux[i] = c[i];
    }

    if (c != NULL) {
        delete[] c;
    }
    
    c = aux;
    tamano = t;
    return true;
}

// Función Amiga: Sobrecarga del operador salida
ostream & operator<<(ostream &os, TVectorCom &v) {
    os << "[";
    for (int i = 0; i < v.tamano; i++) {
        os << "(" << i + 1 << ") " << v.c[i];
        if (i < v.tamano - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}