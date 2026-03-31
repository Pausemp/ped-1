#include "tabbcom.h"
#include <queue>

using namespace std;

// --- Funciones auxiliares globales ---

// Función para determinar si el primer TComplejo es mayor que el segundo
// Basado en las reglas: Módulo -> Parte Real -> Parte Imaginaria
bool MayorQue(TComplejo c1, TComplejo c2) {
    if (c1.Mod() == c2.Mod()) {
        if (c1.Re() == c2.Re()) {
            return c1.Im() > c2.Im();
        } else {
            return c1.Re() > c2.Re();
        }
    } else {
        return c1.Mod() > c2.Mod();
    }
}

// ==========================================
// Implementación de la Clase TNodoABB
// ==========================================

TNodoABB::TNodoABB() : item(), iz(), de() {}

TNodoABB::TNodoABB(TNodoABB &otro) : item(otro.item), iz(otro.iz), de(otro.de) {}

TNodoABB::~TNodoABB() {}

TNodoABB & TNodoABB::operator=(TNodoABB &otro) {
    if (this != &otro) {
        item = otro.item;
        iz = otro.iz;
        de = otro.de;
    }
    return *this;
}

// ==========================================
// Implementación de la Clase TABBCom
// ==========================================

TABBCom::TABBCom() {
    nodo = NULL;
}

TABBCom::TABBCom(TABBCom &otro) {
    if (otro.nodo != NULL) {
        nodo = new TNodoABB();
        nodo->item = otro.nodo->item;
        nodo->iz = otro.nodo->iz;
        nodo->de = otro.nodo->de;
    } else {
        nodo = NULL;
    }
}

TABBCom::~TABBCom() {
    if (nodo != NULL) {
        delete nodo; // Desencadena el borrado recursivo a través del destructor de TNodoABB y TABBCom
        nodo = NULL;
    }
}

TABBCom & TABBCom::operator=(TABBCom &otro) {
    if (this != &otro) {
        if (nodo != NULL) {
            delete nodo;
            nodo = NULL;
        }
        if (otro.nodo != NULL) {
            nodo = new TNodoABB();
            nodo->item = otro.nodo->item;
            nodo->iz = otro.nodo->iz;
            nodo->de = otro.nodo->de;
        }
    }
    return *this;
}

bool TABBCom::EsVacio() {
    return nodo == NULL;
}

bool TABBCom::operator==(TABBCom &otro) {
    // Dos árboles son iguales si poseen los mismos elementos
    // Comparando los vectores devueltos por Inorden, verificamos cantidad y valores fácilmente 
    TVectorCom v1 = this->Inorden();
    TVectorCom v2 = otro.Inorden();
    return v1 == v2;
}

bool TABBCom::Insertar(TComplejo &c) {
    if (EsVacio()) {
        nodo = new TNodoABB();
        nodo->item = c;
        return true;
    }
    if (nodo->item == c) {
        return false; // El elemento ya existe en el árbol, no permitimos duplicados
    }
    
    if (MayorQue(nodo->item, c)) { // El nodo actual es MAYOR que el insertar => ir a la IZQUIERDA
        return nodo->iz.Insertar(c);
    } else { // El nodo actual es MENOR que el elemento => ir a la DERECHA
        return nodo->de.Insertar(c);
    }
}

bool TABBCom::Borrar(TComplejo &c) {
    if (EsVacio()) {
        return false;
    }
    if (nodo->item == c) { // Elemento encontrado
        if (nodo->iz.EsVacio() && nodo->de.EsVacio()) { 
            // Caso 0 hijos (Hoja)
            delete nodo;
            nodo = NULL;
        } else if (nodo->iz.EsVacio()) {
            // Caso 1 hijo a la derecha
            TNodoABB *borrar = nodo;
            nodo = nodo->de.nodo;       // Apuntamos al árbol derecho
            borrar->de.nodo = NULL;     // Desvinculamos para que al hacer delete no borre recursivamente 
            delete borrar;
        } else if (nodo->de.EsVacio()) {
            // Caso 1 hijo a la izquierda
            TNodoABB *borrar = nodo;
            nodo = nodo->iz.nodo;       
            borrar->iz.nodo = NULL;     
            delete borrar;
        } else {
            // Caso 2 hijos: Sustituir por el MAYOR de la IZQUIERDA
            TABBCom *aux = &(nodo->iz);
            // Avanzar hacia la derecha para encontrar el mayor de ese subárbol
            while (!aux->nodo->de.EsVacio()) {
                aux = &(aux->nodo->de);
            }
            TComplejo mayorIzq = aux->nodo->item;
            nodo->item = mayorIzq;           // Sustituimos el elemento a borrar
            nodo->iz.Borrar(mayorIzq);       // Borramos el duplicado recién generado del subárbol izquierdo
        }
        return true;
    } else if (MayorQue(nodo->item, c)) {
        return nodo->iz.Borrar(c);
    } else {
        return nodo->de.Borrar(c);
    }
}

bool TABBCom::Buscar(TComplejo &c) {
    if (EsVacio()) return false;
    if (nodo->item == c) return true;
    
    if (MayorQue(nodo->item, c)) return nodo->iz.Buscar(c);
    return nodo->de.Buscar(c);
}

TComplejo TABBCom::Raiz() {
    if (EsVacio()) {
        TComplejo vacio;
        return vacio;
    }
    return nodo->item;
}

int TABBCom::Altura() {
    if (EsVacio()) return 0;
    
    int altIz = nodo->iz.Altura();
    int altDe = nodo->de.Altura();
    
    if (altIz > altDe) {
        return 1 + altIz;
    } else {
        return 1 + altDe;
    }
}

int TABBCom::Nodos() {
    if (EsVacio()) return 0;
    return 1 + nodo->iz.Nodos() + nodo->de.Nodos();
}

int TABBCom::NodosHoja() {
    if (EsVacio()) return 0;
    if (nodo->iz.EsVacio() && nodo->de.EsVacio()) return 1;
    
    return nodo->iz.NodosHoja() + nodo->de.NodosHoja();
}

// --- Métodos de Recorrido Auxiliares ---

void TABBCom::InordenAux(TVectorCom &v, int &pos) {
    if (!EsVacio()) {
        nodo->iz.InordenAux(v, pos);
        v[pos] = nodo->item;
        pos++;
        nodo->de.InordenAux(v, pos);
    }
}

void TABBCom::PreordenAux(TVectorCom &v, int &pos) {
    if (!EsVacio()) {
        v[pos] = nodo->item;
        pos++;
        nodo->iz.PreordenAux(v, pos);
        nodo->de.PreordenAux(v, pos);
    }
}

void TABBCom::PostordenAux(TVectorCom &v, int &pos) {
    if (!EsVacio()) {
        nodo->iz.PostordenAux(v, pos);
        nodo->de.PostordenAux(v, pos);
        v[pos] = nodo->item;
        pos++;
    }
}

// --- Métodos de Recorrido ---

TVectorCom TABBCom::Inorden() {
    int posicion = 1;
    TVectorCom v(Nodos());
    InordenAux(v, posicion);
    return v;
}

TVectorCom TABBCom::Preorden() {
    int posicion = 1;
    TVectorCom v(Nodos());
    PreordenAux(v, posicion);
    return v;
}

TVectorCom TABBCom::Postorden() {
    int posicion = 1;
    TVectorCom v(Nodos());
    PostordenAux(v, posicion);
    return v;
}

TVectorCom TABBCom::Niveles() {
    TVectorCom v(Nodos());
    if (EsVacio()) return v;

    queue<TABBCom*> q;
    q.push(this);
    int pos = 1;

    while (!q.empty()) {
        TABBCom *actual = q.front();
        q.pop();

        v[pos] = actual->nodo->item;
        pos++;

        if (!actual->nodo->iz.EsVacio()) {
            q.push(&(actual->nodo->iz));
        }
        if (!actual->nodo->de.EsVacio()) {
            q.push(&(actual->nodo->de));
        }
    }
    return v;
}

// --- Amistad Global ---

ostream & operator<<(ostream &os, TABBCom &arbol) {
    TVectorCom v = arbol.Niveles();
    os << v;
    return os;
}