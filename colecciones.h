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
template<typename Elemento> void borrar (coleccion<Elemento>& c, const Elemento& e);

// Si en <c> hay algún elemento igual a <e>, devuelve la colección resultante de borrar de <c>
// el último elemento igual a <e> que fue añadido a la colección.
// En caso contrario devuelve una colección igual a <c>.
template<typename Elemento> void borrarUltimo (coleccion<Elemento>& c, const Elemento& e);

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

template <typename Elemento>
struct coleccion {
    friend void crear<Elemento> (coleccion<Elemento>& c);
    friend void aniadir<Elemento> (coleccion<Elemento>& c, const Elemento& e);
    friend bool esta<Elemento> (const coleccion<Elemento>& c, const Elemento& e);
    friend void obtenerUltimo<Elemento> (const coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo);
    friend void borrar<Elemento> (coleccion<Elemento>& c, const Elemento& e);
    friend void borrarUltimo<Elemento> (coleccion<Elemento>& c, const Elemento& e);
    friend int  tamanio<Elemento> (const coleccion<Elemento>& c);
    friend bool esVacia<Elemento> (const coleccion<Elemento>& c);

    friend void iniciarIterador<Elemento> (coleccion<Elemento>& c);
    friend bool existeSiguiente<Elemento> (const coleccion<Elemento>& c);
    friend bool siguiente<Elemento> (coleccion<Elemento> &c, Elemento& next);
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
void aniadirRec (coleccion<Elemento>& c, const Elemento& e, typename coleccion<Elemento>::Nodo*& Nodo, bool& nuevo) { //PENDIENTE REVISION 
    if (Nodo == nullptr) {
        crearVacia(Nodo->p);
        apilar(Nodo->p, e);
        Nodo->izq = nullptr;
        Nodo->dcha = nullptr;
        nuevo = true;
    } else {
        Elemento dato;
        bool error;
        cima(Nodo->p, dato, error);

        if (e == dato) {
            apilar(Nodo->p, e);
            nuevo = false;
        } else if (e < dato) {
            aniadirRec(c, Nodo->izq, e, nuevo);
        } else {
            aniadirRec(c, Nodo->dcha, e, nuevo);
        }
    }
}

template<typename Elemento>
void aniadir (coleccion<Elemento>& c, const Elemento& e) {
    bool nuevo;
    aniadirRec(c, e, c.raiz, nuevo);
    if (nuevo) c.total++;
}

template<typename Elemento>
void estaRec (const coleccion<Elemento>& c, const Elemento& e, typename coleccion<Elemento>::Nodo*& Nodo, bool& exito) {
    if (esVacia(c)) {
        exito = false;
    } else {
        Elemento dato;
        bool error;
        cima(Nodo->p, dato, error);

        if (e == dato) {
            exito = true;
        } else if (e < dato) {
            estaRec(c, Nodo->izq, exito, e);
        } else {
            estaRec(c, Nodo->dcha, exito, e);
        }
    }
}

template<typename Elemento>
bool esta (const coleccion<Elemento>& c, const Elemento& e) {
    bool exito;
    estaRec(c, e, c.raiz, exito);
    return exito;
}

// PARCIAL: Operación no definida si <e> no esta en c
template<typename Elemento>
void obtenerUltimoRec (const coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo, typename coleccion<Elemento>::Nodo*& Nodo, bool& exito) {
    if (esVacia(c)) {
        exito = false;
    } else {
        Elemento dato;
        bool error;
        cima(Nodo->p, dato, error);

        if (e == dato) {
            exito = true;
            ultimo = dato;
        } else if (e < dato) {
            obtenerUltimoRec(c, e, ultimo, Nodo->izq, exito);
        } else {
            obtenerUltimoRec(c, e, ultimo, Nodo->dcha, exito);
        }
    }
}

template<typename Elemento>
void obtenerUltimo (const coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo) {
    bool exito;
    obtenerUltimoRec(c, e, ultimo, c.raiz, exito);
}

template<typename Elemento>
void borrarRec (coleccion<Elemento>& c, const Elemento e, typename coleccion<Elemento>::Nodo*& Nodo, bool& borrado) {

}

template<typename Elemento>
void borrar (coleccion<Elemento>& c, const Elemento e) {

}

template<typename Elemento>
void borrarUltimoRec (coleccion<Elemento>& c, const Elemento e, typename coleccion<Elemento>::Nodo*& Nodo, bool& borrado) {
    if (esVacia(c)) {
        borrado = false;
    } else {
        Elemento dato;
        bool error;
        cima(Nodo->p, dato, error);

        if (e == dato) {
            borrado = true;
            desapilar(Nodo->p);
        } else if (e < dato) {
            obtenerUltimoRec(c, e, Nodo->izq, borrado);
        } else {
            obtenerUltimoRec(c, e, Nodo->dcha, borrado);
        }
    }
}

template<typename Elemento>
void borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    bool borrado;
    borrarUltimoRec (c, e, c.raiz, borrado);
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>& c) {
    return c.raiz == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    typename coleccion<Elemento>::Nodo* aux = new typename coleccion<Elemento>::Nodo;
    crearVacia(c.iter);
    aux = c.raiz;
    while (aux != nullptr) {
        apilar(c.iter, aux);
        aux = aux->izq;
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return !esVacia(c.iter);
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        typename coleccion<Elemento>::Nodo* aux = new typename coleccion<Elemento>::Nodo;
        aux = cima(c.iter);
        desapilar(c.iter);

        Elemento dato;
        bool error;
        cima(aux->p, dato, error);

        aux = aux->dcha;
        while (aux != nullptr) {
            apilar(c.iter, aux);
            aux = aux->izq;
        }
        return true;    // Error = false
    } else {
        return false;   // Error = true
    }
}

#endif
