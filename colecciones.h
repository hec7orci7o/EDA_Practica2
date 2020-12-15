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
template<typename Elemento> bool esta (const coleccion<Elemento>& c, const Elemento& e);

// Si en <c> hay algún elemento igual a <e>, devuelve el último elemento igual a <e> que fue
// añadido a la colección <c>.
// PARCIAL: Operación no definida si <e> no esta en c
template<typename Elemento> void obtenerUltimo (const coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo);

// Si en <c> hay algún elemento igual a <e>, devuelve la colección resultante de borrar de <c>
// todos los elementos iguales a <e>.
// En caso contrario, devuelve una colección igual a <c>.
template<typename Elemento> void borrar (const coleccion<Elemento>& c, const Elemento& e);

// Si en <c> hay algún elemento igual a <e>, devuelve la colección resultante de borrar de <c>
// el último elemento igual a <e> que fue añadido a la colección.
// En caso contrario devuelve una colección igual a <c>.
template<typename Elemento> void borrarUltimo (coleccion<Elemento>& c, const Elemento& e);

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
template<typename Elemento> bool siguiente (coleccion<Elemento> &c, Elemento& next, bool& error);

// FUNCIONES AUXILIARES, NO USAR BAJO NINGÚN CONCEPTO.
template<typename Elemento> void aniadirRec (const Elemento& e, typename coleccion<Elemento>::Nodo*& Nodo, bool& nuevo);
template<typename Elemento> void estaRec (const Elemento& e, typename coleccion<Elemento>::Nodo*& Nodo, bool& exito);
template<typename Elemento> void obtenerUltimoRec (const Elemento& e, Elemento& ultimo, typename coleccion<Elemento>::Nodo*& Nodo, bool& exito);
template<typename Elemento> void borrarMax (Elemento& e, typename coleccion<Elemento>::Nodo*& Nodo);
template<typename Elemento> void borrarUltimoRec (const Elemento e, typename coleccion<Elemento>::Nodo*& Nodo, bool& borrado);
template<typename Elemento> void borrarRec (const Elemento& e, typename coleccion<Elemento>::Nodo*& Nodo);

template <typename Elemento>
struct coleccion {
    friend void crear<Elemento> (coleccion<Elemento>& c);
    friend void aniadir<Elemento> (coleccion<Elemento>& c, const Elemento& e);
    friend bool esta<Elemento> (const coleccion<Elemento>& c, const Elemento& e);
    friend void obtenerUltimo<Elemento> (const coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo);
    friend void borrar<Elemento> (const coleccion<Elemento>& c, const Elemento& e);
    friend void borrarUltimo<Elemento> (coleccion<Elemento>& c, const Elemento& e);
    friend int  tamanio<Elemento> (const coleccion<Elemento>& c);
    friend bool esVacia<Elemento> (const coleccion<Elemento>& c);

    friend void iniciarIterador<Elemento> (coleccion<Elemento>& c);
    friend bool existeSiguiente<Elemento> (const coleccion<Elemento>& c);
    friend void siguiente<Elemento> (coleccion<Elemento> &c, Elemento& next, bool& error);

    // Funciones auxiliares
    friend void aniadirRec<Elemento> (const Elemento& e, typename coleccion<Elemento>::Nodo*& Nodo, bool& nuevo);
    friend void estaRec<Elemento> (const Elemento& e, typename coleccion<Elemento>::Nodo*& Nodo, bool& exito);
    friend void obtenerUltimoRec<Elemento> (const Elemento& e, Elemento& ultimo, typename coleccion<Elemento>::Nodo*& Nodo, bool& exito);
    friend void borrarMax<Elemento> (Elemento& e, typename coleccion<Elemento>::Nodo*& Nodo);
    friend void borrarUltimoRec<Elemento> (const Elemento e, typename coleccion<Elemento>::Nodo*& Nodo, bool& borrado);
    friend void borrarRec<Elemento> (const Elemento& e, typename coleccion<Elemento>::Nodo*& Nodo);
    private:
            struct Nodo {
            pila<Elemento> p;
            Nodo* izq;
            Nodo* dcha;
        };
        pila<Nodo*> iter;
        Nodo* raiz;
        int total;
};

template<typename Elemento>
void crear (coleccion<Elemento>& c) {
    c.raiz = nullptr;
    c.total = 0;
}

template<typename Elemento>
void aniadirRec (const Elemento& e, typename coleccion<Elemento>::Nodo*& Nodo, bool& nuevo) {
    if (Nodo == nullptr) {
        crearVacia<Elemento> (Nodo->p);
        apilar<Elemento> (Nodo->p, e);
        Nodo->izq = nullptr;
        Nodo->dcha = nullptr;
        nuevo = true;
    } else {
        Elemento dato;
        bool error;
        cima<Elemento> (Nodo->p, dato, error);

        if (e == dato) {
            apilar<Elemento> (Nodo->p, e);
            nuevo = false;
        } else if (e < dato) {
            aniadirRec<Elemento> (Nodo->izq, e, nuevo);
        } else {
            aniadirRec<Elemento> (Nodo->dcha, e, nuevo);
        }
    }
}

template<typename Elemento>
void aniadir (coleccion<Elemento>& c, const Elemento& e) {
    bool nuevo;
    aniadirRec<Elemento> (e, c.raiz, nuevo);
    if (nuevo) c.total++;
}

template<typename Elemento>
void estaRec (const Elemento& e, typename coleccion<Elemento>::Nodo*& Nodo, bool& exito) {
    if (Nodo == nullptr) {
        exito = false;
    } else {
        Elemento dato;
        bool error;
        cima<Elemento> (Nodo->p, dato, error);

        if (e == dato) {
            exito = true;
        } else if (e < dato) {
            estaRec<Elemento> (e, Nodo->izq, exito);
        } else {
            estaRec<Elemento> (e, Nodo->dcha, exito);
        }
    }
}

template<typename Elemento>
bool esta (const coleccion<Elemento>& c, const Elemento& e) {
    bool exito;
    estaRec<Elemento> (e, c.raiz, exito);
    return exito;
}

// PARCIAL: Operación no definida si <e> no esta en c
template<typename Elemento>
void obtenerUltimoRec (const Elemento& e, Elemento& ultimo, typename coleccion<Elemento>::Nodo*& Nodo, bool& exito) {
    if (Nodo == nullptr) {
        exito = false;
    } else {
        Elemento dato;
        bool error;
        cima<Elemento> (Nodo->p, dato, error);

        if (e == dato) {
            exito = true;
            ultimo = dato;
        } else if (e < dato) {
            obtenerUltimoRec<Elemento> (e, ultimo, Nodo->izq, exito);
        } else {
            obtenerUltimoRec<Elemento> (e, ultimo, Nodo->dcha, exito);
        }
    }
}

template<typename Elemento>
void obtenerUltimo (const coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo) {
    bool exito;
    obtenerUltimoRec<Elemento> (e, ultimo, c.raiz, exito);
}

template<typename Elemento>
void borrarMax (Elemento& e, typename coleccion<Elemento>::Nodo*& Nodo) {
    if (Nodo->dcha == nullptr) {    // El máximo del árbol esta en la raiz
        typename coleccion<Elemento>::Nodo* aux = new typename coleccion<Elemento>::Nodo;

        Elemento dato;
        bool error;
        cima<Elemento> (Nodo->p, dato, error);
        
        e = dato;
        aux = Nodo;
        Nodo = Nodo->izq;
        delete aux;
    } else {    // El máximo del árbol esta en el subárbol derecho
        borrarMax<Elemento> (e, Nodo->dcha);
    }
}

template<typename Elemento>
void borrarRec (const Elemento& e, typename coleccion<Elemento>::Nodo*& Nodo) {
    if (Nodo != nullptr) {
        Elemento dato;
        bool error;
        cima<Elemento> (Nodo->p, dato, error);

        if (e == dato) {    // Elemento encontrado
            typename coleccion<Elemento>::Nodo* aux = new typename coleccion<Elemento>::Nodo;
            liberar<Elemento> (Nodo->p);
            if (Nodo->izq == nullptr) { // Sustitucion del nodo por su sucesor(derecho)
                aux = Nodo;
                Nodo = Nodo->dcha;
                delete aux;
            } else {
                borrarMax<Elemento> (e, Nodo->izq);  // Si tiene hijo izquierdo...
            }
        } else if (e < dato) {
            borrarRec<Elemento> (e, Nodo);
        } else {
            borrarRec<Elemento> (e, Nodo);
        }
    }
}

template<typename Elemento>
void borrar (const coleccion<Elemento>& c, const Elemento& e) {
    borrarRec<Elemento> (e, c.raiz);
}

// Sobra c
template<typename Elemento>
void borrarUltimoRec (const Elemento e, typename coleccion<Elemento>::Nodo*& Nodo, bool& borrado) {
    if (Nodo == nullptr) {
        borrado = false;
    } else {
        Elemento dato;
        bool error;
        cima<Elemento> (Nodo->p, dato, error);

        if (e == dato) {    // si desapilo el ultimo??
            borrado = true;
            desapilar<Elemento> (Nodo->p);
        } else if (e < dato) {
            obtenerUltimoRec<Elemento> (e, Nodo->izq, borrado);
        } else {
            obtenerUltimoRec<Elemento> (e, Nodo->dcha, borrado);
        }
    }
}

template<typename Elemento>
void borrarUltimo (coleccion<Elemento>& c, const Elemento& e) {
    bool borrado;
    borrarUltimoRec<Elemento> (e, c.raiz, borrado);
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
    typename coleccion<Elemento>::Nodo* aux = new typename coleccion<Elemento>::Nodo;
    crearVacia<Elemento> (c.iter);
    aux = c.raiz;
    while (aux != nullptr) {
        apilar<Elemento> (c.iter, aux);
        aux = aux->izq;
    }
}

template<typename Elemento>
bool existeSiguiente (const coleccion<Elemento>& c) {
    return !esVacia<Elemento> (c.iter);
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento>
void siguiente (coleccion<Elemento> &c, Elemento& next, bool& error) {
    if (existeSiguiente<Elemento> (c)) {
        typename coleccion<Elemento>::Nodo* aux = new typename coleccion<Elemento>::Nodo;
        aux = cima<Elemento> (c.iter);
        desapilar<Elemento> (c.iter);

        cima<Elemento> (aux->p, next, error);
        aux = aux->dcha;
        while (aux != nullptr) {
            apilar<Elemento> (c.iter, aux);
            aux = aux->izq;
        }
        error = false;  // Error = false
    } else {
        error = true;   // Error = true
    }
}

#endif