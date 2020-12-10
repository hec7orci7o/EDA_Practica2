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

// El TAD <coleccion> representa colecciones de elementos ordenados de menor a mayor, en las que
// puede haber elementos "iguales".
// Los elementos iguales se mantendrán ordenados según su orden de incorporación a la colección.
template<typename Elemento> struct coleccion;

// Crea una colección vacia sin elementos.
template<typename Elemento> void crear (coleccion<Elemento>& c);

// Devuelve la colección resultante de añadir el elemento <e> a la colección <c>.
// RECORDAR: <c> esta ordenada de menor -> mayor.
// Si en <c> ya había algún elemento igual a <e>, este quedará como el último de todos los iguales.
template<typename Elemento> bool aniadir (coleccion<Elemento>& c, const Elemento e);

// Devuelve "TRUE" si y solo si en <c> hay algún elemento igual a <e>.
template<typename Elemento> bool esta (const coleccion<Elemento>& c, const Elemento e);

// Si en <c> hay algún elemento igual a <e>, devuelve el último elemento igual a <e> que fue
// añadido a la colección <c>.
// PARCIAL: Operación no definida si <e> no esta en c
template<typename Elemento> bool obtenerUltimo (const coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo);

// Si en <c> hay algún elemento igual a <e>, devuelve la colección resultante de borrar de <c>
// todos los elementos iguales a <e>.
// En caso contrario, devuelve una colección igual a <c>.
template<typename Elemento> bool borrar (coleccion<Elemento>& c, const Elemento e);

// Si en <c> hay algún elemento igual a <e>, devuelve la colección resultante de borrar de <c>
// el último elemento igual a <e> que fue añadido a la colección.
// En caso contrario devuelve una colección igual a <c>.
template<typename Elemento> bool borrarUltimo (coleccion<Elemento>& c, const Elemento e);

// Devuelve el número total de elementos de la colección.
template<typename Elemento> int tamanio (const coleccion<Elemento>& c);

// Devuelve "TRUE" si y solo si <c> no tiene ningún elemento.
template<typename Elemento> bool esVacia (const coleccion<Elemento> c);

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
    friend bool aniadir<Elemento> (coleccion<Elemento>& c, const Elemento e);
    friend bool esta<Elemento> (const coleccion<Elemento>& c, const Elemento e);
    friend bool obtenerUltimo<Elemento> (const coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo);
    friend bool borrar<Elemento> (coleccion<Elemento>& c, const Elemento e);
    friend bool borrarUltimo<Elemento> (coleccion<Elemento>& c, const Elemento e);
    friend int  tamanio<Elemento> (const coleccion<Elemento>& c);
    friend bool esVacia<Elemento> (const coleccion<Elemento> c);

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

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
void aniadirRec (coleccion<Elemento>& c, typename coleccion<Elemento>::Nodo*& Nodo, const Elemento e, bool& nuevo) { //PENDIENTE REVISION 
    if (Nodo == nullptr) {
        crearVacia(Nodo->p);
        apilar(Nodo->p, e);
        Nodo->izq = nullptr;
        Nodo->dcha = nullptr;
        nuevo = true;
    } else {
        Elemento dato;
        bool error;
        cima (Nodo->p, dato, error);

        if (e == dato) {
            apilar(c, Nodo->p, e);
            nuevo = false;
        } else if (e < dato) {
            aniadir(c, Nodo->izq, e);
        } else {
            aniadir(c, Nodo->dcha, e);
        }
    }
}

template<typename Elemento>
void aniadir (coleccion<Elemento>& c, const Elemento e) {
    bool nuevo;
    aniadirRec(c, c.raiz, e, nuevo);
    if (nuevo) c.total++;
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool estaRec (coleccion<Elemento>& c, typename coleccion<Elemento>::Nodo*& Nodo, bool& exito, Elemento& e) {
    if (esVacia(c)) {
        exito = false;
    } else {
        Elemento dato;      // PASAR POR REF
        bool error;
        cima (c.raiz->p, dato, error);

        if (e == dato) {
            exito = true;
        } else if (e < dato) {
            aniadir(c, c.raiz->izq, e);
        } else {
            aniadir(c, c.raiz->dcha, e);
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool esta (coleccion<Elemento>& c, typename coleccion<Elemento>::Nodo*& Nodo, bool& exito, Elemento& e) {
    bool exito;
    estaRec(c, c.raiz, exito, e);
    return exito;
}

// PARCIAL: Operación no definida si <e> no esta en c
template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
void obtenerUltimoRec (const coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo) {
    if (esVacia(c)) {
        error = true;
    } else {
        Elemento dato;      // PASAR POR REF
        bool error;
        cima (c.raiz->p, dato, error);

        if (e == dato) {
            error = false;
        } else if (e < dato) {
            aniadir(c, c.raiz->izq, e);
        } else {
            aniadir(c, c.raiz->dcha, e);
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
void obtenerUltimo (const coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo) {
    bool error;
    obtenerUltimoRec(c, c.raiz, error, e);
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrar (coleccion<Elemento>& c, const Elemento e) {

}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {

}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento> c) {
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
    typename coleccion<Elemento>::Nodo* aux = new typename coleccion<Elemento>::Nodo;
    if (existeSiguiente(c)) {
        error = false;
        aux = cima(c.iter);
        desapilar(c.iter);

        Elemento dato;
        bool error;
        cima(aux->p, dato, errorDato);

        aux = aux->dcha;
        while (aux != nullptr) {
            apilar(c.iter, aux);
            aux = aux->izq;
        }
    } else {
        error = true;
    }
}

#endif
