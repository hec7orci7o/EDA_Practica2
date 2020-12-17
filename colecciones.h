//-------------------------------------------------------------------------------------------
// File:    colecciones.h
// Authors: Pablo Lacueva(799134) & Hector Toral(798095)
// Date:    nov 2020
// Coms:    Practica 1 de EDA
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
template<typename Elemento> void aniadir (coleccion<Elemento>& c, const Elemento& e);

// Devuelve "TRUE" si y solo si en <c> hay algún elemento igual a <e>.
template<typename Elemento> bool esta (coleccion<Elemento>& c, const Elemento& e);

// Si en <c> hay algún elemento igual a <e>, devuelve el último elemento igual a <e> que fue
// añadido a la colección <c>.
// PARCIAL: Operación no definida si <e> no esta en c
template<typename Elemento> void obtenerUltimo (coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo);

// Si en <c> hay algún elemento igual a <e>, devuelve la colección resultante de borrar de <c>
// todos los elementos iguales a <e>.
// En caso contrario, devuelve una colección igual a <c>.
template<typename Elemento> void borrar (coleccion<Elemento>& c, Elemento& e);

// Si en <c> hay algún elemento igual a <e>, devuelve la colección resultante de borrar de <c>
// el último elemento igual a <e> que fue añadido a la colección.
// En caso contrario devuelve una colección igual a <c>.
template<typename Elemento> void borrarUltimo (coleccion<Elemento>& c, Elemento& e);

// Devuelve el número total de elementos de la colección.
template<typename Elemento> int  tamanio (const coleccion<Elemento>& c);

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
template<typename Elemento> void siguiente (coleccion<Elemento> &c, Elemento& next, bool& error);

// FUNCIONES AUXILIARES, NO USAR BAJO NINGÚN CONCEPTO.
template<typename Elemento> void aniadirRec (const Elemento& e, typename coleccion<Elemento>::Nodo*& nodo);
template<typename Elemento> void estaRec (const Elemento& e, typename coleccion<Elemento>::Nodo*& nodo, bool& exito);
template<typename Elemento> void obtenerUltimoRec (const Elemento& e, Elemento& ultimo, typename coleccion<Elemento>::Nodo*& nodo, bool& exito);
template<typename Elemento> void borrarMax (pila<Elemento>& e, typename coleccion<Elemento>::Nodo*& nodo);
template<typename Elemento> void borrarUltimoRec (Elemento& e, typename coleccion<Elemento>::Nodo*& nodo, bool& borrado);
template<typename Elemento> void borrarRec (Elemento& e, typename coleccion<Elemento>::Nodo*& nodo);

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
        friend void aniadir<Elemento> (coleccion<Elemento>& c, const Elemento& e);
        friend bool esta<Elemento> (coleccion<Elemento>& c, const Elemento& e);
        friend void obtenerUltimo<Elemento> (coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo);
        friend void borrar<Elemento> (coleccion<Elemento>& c, Elemento& e);
        friend void borrarUltimo<Elemento> (coleccion<Elemento>& c, Elemento& e);
        friend int  tamanio<Elemento> (const coleccion<Elemento>& c);
        friend bool esVacia<Elemento> (const coleccion<Elemento>& c);

        friend void iniciarIterador<Elemento> (coleccion<Elemento>& c);
        friend bool existeSiguiente<Elemento> (const coleccion<Elemento>& c);
        friend void siguiente<Elemento> (coleccion<Elemento> &c, Elemento& next, bool& error);

        // Funciones auxiliares
        friend void aniadirRec<Elemento> (const Elemento& e, coleccion<Elemento>::Nodo*& nodo);
        friend void estaRec<Elemento> (const Elemento& e, coleccion<Elemento>::Nodo*& nodo, bool& exito);
        friend void obtenerUltimoRec<Elemento> (const Elemento& e, Elemento& ultimo, coleccion<Elemento>::Nodo*& nodo, bool& exito);
        friend void borrarMax<Elemento> (pila<Elemento>& e, coleccion<Elemento>::Nodo*& nodo);
        friend void borrarUltimoRec<Elemento> (Elemento& e, coleccion<Elemento>::Nodo*& nodo, bool& borrado);
        friend void borrarRec<Elemento> (Elemento& e, coleccion<Elemento>::Nodo*& nodo);
};

template<typename Elemento>
void crear (coleccion<Elemento>& c) {
    c.raiz = nullptr;
    c.total = 0;
}

template<typename Elemento>
void aniadirRec (const Elemento& e, typename coleccion<Elemento>::Nodo*& nodo) {
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
            aniadirRec(e, nodo->izq);
        } else {
            aniadirRec(e, nodo->dcha);
        }
    }
}

template<typename Elemento>
void aniadir (coleccion<Elemento>& c, const Elemento& e) {
    aniadirRec<Elemento> (e, c.raiz);
    c.total++;
}

template<typename Elemento>
void estaRec (const Elemento& e, typename coleccion<Elemento>::Nodo*& nodo, bool& exito) {
    if (nodo == nullptr) {
        exito = false;
    } else {
        Elemento dato;
        bool error;
        cima(nodo->p, dato, error);

        if (e == dato) {
            exito = true;
        } else if (e < dato) {
            estaRec(e, nodo->izq, exito);
        } else {
            estaRec(e, nodo->dcha, exito);
        }
    }
}

template<typename Elemento>
bool esta (coleccion<Elemento>& c, const Elemento& e) {
    bool exito = false;
    estaRec<Elemento> (e, c.raiz, exito);
    return exito;
}

// PARCIAL: Operación no definida si <e> no esta en c
template<typename Elemento>
void obtenerUltimoRec (const Elemento& e, Elemento& ultimo, typename coleccion<Elemento>::Nodo*& nodo, bool& exito) {
    if (nodo == nullptr) {
        exito = false;
    } else {
        Elemento dato;
        bool error;
        cima(nodo->p, dato, error);

        if (e == dato) {
            exito = true;
            ultimo = dato;
        } else if (e < dato) {
            obtenerUltimoRec(e, ultimo, nodo->izq, exito);
        } else {
            obtenerUltimoRec(e, ultimo, nodo->dcha, exito);
        }
    }
}

template<typename Elemento>
void obtenerUltimo (coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo) {
    bool exito;
    obtenerUltimoRec<Elemento> (e, ultimo, c.raiz, exito);
}

template<typename Elemento>
void borrarMax (pila<Elemento>& e, typename coleccion<Elemento>::Nodo*& nodo) {
    if (nodo->dcha == nullptr) {    // El máximo del árbol esta en la raiz
        typename coleccion<Elemento>::Nodo* aux;
        e = nodo->p;

        aux = nodo;
        nodo = nodo->izq;
        delete aux;
    } else {    // El máximo del árbol esta en el subárbol derecho
        borrarMax (e, nodo->dcha);
    }
}

template<typename Elemento>
void borrarRec (Elemento& e, typename coleccion<Elemento>::Nodo*& nodo) {
    if (nodo != nullptr) {
        Elemento dato;
        bool error;
        cima(nodo->p, dato, error);

        if (e == dato) {    // Elemento encontrado
            typename coleccion<Elemento>::Nodo* aux;
            liberar(nodo->p);
            if (nodo->izq == nullptr) { // Sustitucion del nodo por su sucesor(derecho)
                aux = nodo;
                nodo = nodo->dcha;
                delete aux;
            } else {
                borrarMax(nodo->p, nodo->izq);  // Si tiene hijo izquierdo...
            }
        } else if (e < dato) {
            borrarRec(e, nodo->izq);
        } else {
            borrarRec(e, nodo->dcha);
        }
    }
}

template<typename Elemento>
void borrar (coleccion<Elemento>& c, Elemento& e) {
    borrarRec<Elemento> (e, c.raiz);
}

template<typename Elemento>
void borrarUltimoRec (Elemento& e, typename coleccion<Elemento>::Nodo*& nodo, bool& borrado) {
    if (nodo != nullptr) {
        Elemento dato;
        bool error;
        cima(nodo->p, dato, error);

        if (e == dato) {    // Elemento encontrado
            borrado = true;
            desapilar(nodo->p);
            if (esVacia(nodo->p)) {
                if (nodo->izq == nullptr) { // Sustitución del nodo por su sucesor(derecho)
                    typename coleccion<Elemento>::Nodo* aux = new typename coleccion<Elemento>::Nodo;
                    aux = nodo;
                    nodo = nodo->dcha;
                    delete aux;
                } else {    // igual falta el si derecha es nullptr
                    borrarMax(nodo->p, nodo->izq);  // Si tiene hijo izquierdo...
                }
            }
        } else if (e < dato) {
            borrarUltimoRec(e, nodo->izq, borrado);
        } else {
            borrarUltimoRec(e, nodo->dcha, borrado);
        }
    } else {
        borrado = false;
    }
}

template<typename Elemento>
void borrarUltimo (coleccion<Elemento>& c, Elemento& e) {
    bool borrado = false;
    borrarUltimoRec<Elemento> (e, c.raiz, borrado);
    if (borrado) c.total--;
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
void siguiente (coleccion<Elemento> &c, Elemento& next, bool& error) {
    if (existeSiguiente(c)) {
        typename coleccion<Elemento>::Nodo* aux;
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
        error = false;
    } else {
        error = true;
    }
}

#endif