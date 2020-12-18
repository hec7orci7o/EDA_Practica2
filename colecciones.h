//-------------------------------------------------------------------------------------------
// File:    colecciones.h
// Authors: Pablo Lacueva(799134) & Hector Toral(798095)
// Date:    nov 2020
// Coms:    Practica 2 de EDA
//          Link del repositorio: https://github.com/hec7orci7o/EDA_Practica1
//-------------------------------------------------------------------------------------------

#ifndef COLECCIONES_H
#define COLECCIONES_H

#include <iostream>
#include "pila.h"

using namespace std;

// IMPORTANTE: El typename Elemento deberá tener sobrecargado los operadores "==" y "<"

// El TAD <coleccion> representa colecciones de elementos ordenados en un árbol binario de busqueda, en el que
// puede haber elementos "iguales" dentro de un mismo nodo.
// Los elementos iguales se mantendrán ordenados según su orden de incorporación a la colección.
template<typename Elemento> struct coleccion;

// Crea una colección vacia sin elementos.
template<typename Elemento> void crear (coleccion<Elemento>& c);

// Devuelve la colección resultante de añadir el elemento <e> a la colección <c>.
// RECORDAR: los elementos de <c> se ordenan asi:
// Elementos menores en un subárbol izquierdo, mayores en el derecho e iguales en el mismo nodo.
// Si en <c> ya había algún elemento igual a <e>, este quedará como el último de todos los iguales.
template<typename Elemento> void anyadir (coleccion<Elemento>& c, const Elemento& e);

// Devuelve "TRUE" si y solo si en <c> hay algún elemento igual a <e>.
template<typename Elemento> bool esta (coleccion<Elemento>& c, const Elemento& e);

// Si en <c> hay algún elemento igual a <e>, devuelve el último elemento igual a <e> que fue
// añadido a la colección <c>.
// PARCIAL: Operación no definida si <e> no esta en c
template<typename Elemento> bool obtenerUltimo (coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo);

// Si en <c> hay algún elemento igual a <e>, devuelve la colección resultante de borrar de <c>
// todos los elementos iguales a <e>.
// En caso contrario, devuelve una colección igual a <c>.
template<typename Elemento> bool borrar (coleccion<Elemento>& c, Elemento& e);

// Si en <c> hay algún elemento igual a <e>, devuelve la colección resultante de borrar de <c>
// el último elemento igual a <e> que fue añadido a la colección.
// En caso contrario devuelve una colección igual a <c>.
template<typename Elemento> bool borrarUltimo (coleccion<Elemento>& c, Elemento& e);

// Devuelve el número total de elementos de la colección.
template<typename Elemento> int tamanio (const coleccion<Elemento>& c);

// Devuelve "TRUE" si y solo si <c> no tiene ningún elemento.
template<typename Elemento> bool esVacia (const coleccion<Elemento>& c);

// Inicializa el iterador para recorrer los elementos de la colección <c>, de forma que el
// siguiente elemento a visitar sea el primero.
template<typename Elemento> void iniciarIterador (coleccion<Elemento>& c);

// Devuelve "TRUE" si queda algún elemento por visitar con el iterador de la colección <c>,
// devuelve "FALSE" si ya se ha visitado el último elemento.
template<typename Elemento> bool existeSiguiente (const coleccion<Elemento>& c);

// Devuelve el siguiente elemento a visitar con el iterador de la colección <c> y avanza el iterador
// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> bool siguiente (coleccion<Elemento> &c, Elemento& next);

// FUNCIONES AUXILIARES, NO USAR BAJO NINGÚN CONCEPTO.
template<typename Elemento> void anyadirRec (const Elemento& e, typename coleccion<Elemento>::Nodo*& nodo);
template<typename Elemento> bool estaRec (typename coleccion<Elemento>::Nodo*& nodo, const Elemento& e);
template<typename Elemento> bool obtenerUltimoRec (typename coleccion<Elemento>::Nodo*& nodo, const Elemento& e, Elemento& ultimo);
template<typename Elemento> void borrarMax (typename coleccion<Elemento>::Nodo*& nodo, pila<Elemento>& e);
template<typename Elemento> bool borrarUltimoRec (typename coleccion<Elemento>::Nodo*& nodo, Elemento& e);
template<typename Elemento> int  borrarRec (typename coleccion<Elemento>::Nodo*& nodo, Elemento& e);

template <typename Elemento>
struct coleccion {
    private:
        struct Nodo {
            pila<Elemento> p;
            Nodo* izq;
            Nodo* dcha;
        };
        pila<Nodo*> iter;
        Nodo* raiz;
        int total;
    public:
        friend void crear<Elemento> (coleccion<Elemento>& c);
        friend void anyadir<Elemento> (coleccion<Elemento>& c, const Elemento& e);
        friend bool esta<Elemento> (coleccion<Elemento>& c, const Elemento& e);
        friend bool obtenerUltimo<Elemento> (coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo);
        friend bool borrar<Elemento> (coleccion<Elemento>& c, Elemento& e);
        friend bool borrarUltimo<Elemento> (coleccion<Elemento>& c, Elemento& e);
        friend int tamanio<Elemento> (const coleccion<Elemento>& c);
        friend bool esVacia<Elemento> (const coleccion<Elemento>& c);

        friend void iniciarIterador<Elemento> (coleccion<Elemento>& c);
        friend bool existeSiguiente<Elemento> (const coleccion<Elemento>& c);
        friend bool siguiente<Elemento> (coleccion<Elemento> &c, Elemento& next);

        // Funciones auxiliares
        friend void anyadirRec<Elemento> (const Elemento& e, coleccion<Elemento>::Nodo*& nodo);
        friend bool estaRec<Elemento> (coleccion<Elemento>::Nodo*& nodo, const Elemento& e);
        friend bool obtenerUltimoRec<Elemento> (coleccion<Elemento>::Nodo*& nodo, const Elemento& e, Elemento& ultimo);
        friend void borrarMax<Elemento> (coleccion<Elemento>::Nodo*& nodo, pila<Elemento>& e);
        friend bool borrarUltimoRec<Elemento> (coleccion<Elemento>::Nodo*& nodo, Elemento& e);
        friend int  borrarRec<Elemento> (coleccion<Elemento>::Nodo*& nodo, Elemento& e);
};

template<typename Elemento>
void crear (coleccion<Elemento>& c) {
    c.raiz = nullptr;
    c.total = 0;
}

template<typename Elemento>
void anyadirRec (const Elemento& e, typename coleccion<Elemento>::Nodo*& nodo) {
    if (nodo == nullptr) {
        nodo = new typename coleccion<Elemento>::Nodo;
        crearVacia(nodo->p);
        apilar(nodo->p, e);
        nodo->izq = nullptr;
        nodo->dcha = nullptr;
    } else {
        Elemento dato;
        bool error;
        cima(nodo->p, dato, error);

        if (e == dato) {
            apilar(nodo->p, e);
        } else if (e < dato) {
            anyadirRec(e, nodo->izq);
        } else {
            anyadirRec(e, nodo->dcha);
        }
    }
}

template<typename Elemento>
void anyadir (coleccion<Elemento>& c, const Elemento& e) {
    anyadirRec<Elemento> (e, c.raiz);
    c.total++;
}

template<typename Elemento>
bool estaRec (typename coleccion<Elemento>::Nodo*& nodo, const Elemento& e) {
    if (nodo == nullptr) {
        return false;
    } else {
        Elemento dato;
        bool error;
        cima(nodo->p, dato, error);

        if (e == dato) {
            return true;
        } else if (e < dato) {
            return estaRec(nodo->izq, e);
        } else {
            return estaRec(nodo->dcha, e);
        }
    }
}

template<typename Elemento>
bool esta (coleccion<Elemento>& c, const Elemento& e) {
    return estaRec<Elemento> (c.raiz, e);
}

// PARCIAL: Operación no definida si <e> no esta en c
template<typename Elemento>
bool obtenerUltimoRec (typename coleccion<Elemento>::Nodo*& nodo, const Elemento& e, Elemento& ultimo) {
    if (nodo == nullptr) {
        return false;
    } else {
        Elemento dato;
        bool error;
        cima(nodo->p, dato, error);

        if (e == dato) {
            ultimo = dato;
            return true;
        } else if (e < dato) {
            return obtenerUltimoRec(nodo->izq, e, ultimo);
        } else {
            return obtenerUltimoRec(nodo->dcha, e, ultimo);
        }
    }
}

template<typename Elemento>
bool obtenerUltimo (coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo) {
    return obtenerUltimoRec<Elemento> (c.raiz, e, ultimo);
}

template<typename Elemento>
void borrarMax (typename coleccion<Elemento>::Nodo*& nodo, pila<Elemento>& e) {
    if (nodo->dcha == nullptr) {    // El máximo del árbol esta en la raiz
        typename coleccion<Elemento>::Nodo* aux;
        e = nodo->p;
        aux = nodo;
        nodo = nodo->izq;
        delete aux;
    } else {    // El máximo del árbol esta en el subárbol derecho
        borrarMax (nodo->dcha, e);
    }
}

template<typename Elemento>
int borrarRec (typename coleccion<Elemento>::Nodo*& nodo, Elemento& e) {
    if (nodo != nullptr) {
        Elemento dato;
        bool error;
        cima(nodo->p, dato, error);

        if (e == dato) {    // Elemento encontrado
            typename coleccion<Elemento>::Nodo* aux;
            int totalBorrados = altura(nodo->p);
            liberar(nodo->p);
            if (nodo->izq == nullptr) { // Sustitucion del nodo por su sucesor(derecho)
                aux = nodo;
                nodo = nodo->dcha;
                delete aux;
            } else {
                borrarMax(nodo->izq, nodo->p);  // Si tiene ambos hijos...
            }
            return totalBorrados;
        } else if (e < dato) {
            return borrarRec(nodo->izq, e);
        } else {
            return borrarRec(nodo->dcha, e);
        }
    } else {
        return 0;
    }
}

template<typename Elemento>
bool borrar (coleccion<Elemento>& c, Elemento& e) {
    int totalBorrados = borrarRec<Elemento> (c.raiz, e);
    if (totalBorrados > 0) {
        c.total -= totalBorrados;
        return true;
    } else {
        return false;
    }
}

template<typename Elemento>
bool borrarUltimoRec (typename coleccion<Elemento>::Nodo*& nodo, Elemento& e) {
    if (nodo != nullptr) {
        Elemento dato;
        bool error;
        cima(nodo->p, dato, error);

        if (e == dato) {    // Elemento encontrado
            typename coleccion<Elemento>::Nodo* aux;
            desapilar(nodo->p);
            if (esVacia(nodo->p)) {
                if (nodo->izq == nullptr) { // Sustitucion del nodo por su sucesor(derecho)
                    aux = nodo;
                    nodo = nodo->dcha;
                    delete aux;
                } else {
                    borrarMax(nodo->izq, nodo->p);  // Si tiene ambos hijos...
                }
            }
            return true;
        } else if (e < dato) {
            return borrarUltimoRec(nodo->izq, e);
        } else {
            return borrarUltimoRec(nodo->dcha, e);
        }
    } else {
        return 0;
    }
}

template<typename Elemento>
bool borrarUltimo (coleccion<Elemento>& c, Elemento& e) {
    if (borrarUltimoRec<Elemento> (c.raiz, e)) {
        c.total--;
        return true;
    } else {
        return false;
    }
}

template<typename Elemento>
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento>
bool esVacia (const coleccion<Elemento>& c) {
    return c.raiz == nullptr;
}

template<typename Elemento>
void iniciarIterador (coleccion<Elemento>& c) {
    typename coleccion<Elemento>::Nodo* aux;
    crearVacia (c.iter);
    aux = c.raiz;
    while (aux != nullptr) {
        iniciarIterador (aux->p);
        apilar (c.iter, aux);
        aux = aux->izq;
    }
}

template<typename Elemento>
bool existeSiguiente (const coleccion<Elemento>& c) {
    return !esVacia (c.iter);
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento>
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        typename coleccion<Elemento>::Nodo* aux;
        bool error;
        cima(c.iter, aux, error);
        siguiente(aux->p, next, error);

        if (!existeSiguiente(aux->p)) {
            desapilar(c.iter);
            cima(aux->p, next, error);
            aux = aux->dcha;
            while (aux != nullptr) {
                iniciarIterador (aux->p);
                apilar(c.iter, aux);
                aux = aux->izq;
            }
        }
        return true;
    } else {
        return false;
    }
}

#endif