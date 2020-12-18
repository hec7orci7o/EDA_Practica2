//-------------------------------------------------------------------------------------------
// File:    pila.h
// Authors: Pablo Lacueva(799134) & Hector Toral(798095)
// Date:    dic 2020
// Coms:    Practica 2 de EDA
//          Link del repositorio: https://github.com/hec7orci7o/EDA_Practica2
//-------------------------------------------------------------------------------------------

#ifndef PILA_H
#define PILA_H

#include <iostream>

using namespace std;

// El TAD <pila> representa una pila de elementos genérica. En este caso,
// se trata de una pila doblemente enlazada.
template<typename Elemento> struct pila;

// Devuelve una pila vacía, sin elementos.
template<typename Elemento> void crearVacia (pila<Elemento>& p);

// Devuelve la pila resultante de añádir <e> a <p>.
template<typename Elemento> void apilar (pila<Elemento>& p, const Elemento& e);

// Si p es no vacia, devuelve la pila resultante de eliminar de <p>
// el último elemento que fue apilado. Si <p> es vacía, la deja igual.
template<typename Elemento> void desapilar (pila<Elemento>& p);

// Si <p> es vacía, error toma el valor verdad y se deja <e> indefinido.
// si <p> no es vacia, error toma el valor falso y <e> toma el valor de la cima de <p>.
template<typename Elemento> void cima (const pila<Elemento>& p, Elemento& e, bool& error);

// Devuelve verdad si y solo si <p> no tiene elementos.
template<typename Elemento> bool esVacia (const pila<Elemento>& p);

// Devuelve el número de elementos de <p>, 0 si no tiene elementos.
template<typename Elemento> int altura (const pila<Elemento>& p);

// Devuelve verdad si y solo si pila1 y pila2 almacenan la misma pila.
template<typename Elemento> bool operator== (const pila<Elemento>& pila1, const pila<Elemento>& pila2);

// Devuelve la pila vacía, liberando previamente toda la memoria que ocupa la pila de entrada <p>.
template<typename Elemento> void liberar (pila<Elemento>& p);

// Prepara el iterador para que el siguiente elemento a visitar sea la cima de la pila <p>,
// si existe(situacion de no haber visitado ningun elemento).
template<typename Elemento> void iniciarIterador (pila<Elemento>& p);

// Devuelve falso si ya se han visitado todos los elementos de <p>.
// Devuelve verdad en caso contrario.
template<typename Elemento> bool existeSiguiente (const pila<Elemento>& p);

// Implementa las operaciones "siguiente" y "avanza" de la especificación, es decir:
// Si existeSiguiente(p), error toma el valor falso, <e> toma el valor del siguiente
// elemento de la pila, y se avanza el iterador al elemento siguiente de la pila.
// Si no existeSiguiente(p), error toma el valor verdad, <e> queda indefinido y <p> queda como estaba.
template<typename Elemento> bool siguiente (pila<Elemento>& p, Elemento& e);

template <typename Elemento>
struct pila {
    private:
        struct unDato {
            Elemento dato;  // dato de tipo <Elemento>. <Elemento> es un tipo generico
            unDato* sig;    // puntero que apunta a la futura cima.
            unDato* ant;    // puntero que apunta al dato anterior.
        };
        unDato* cim;
        unDato* bas;
        unDato* iter;
        int alt;
    public:
        friend void crearVacia<Elemento> (pila<Elemento>& p);
        friend void apilar<Elemento> (pila<Elemento>& p, const Elemento& e);
        friend void desapilar<Elemento> (pila<Elemento>& p);
        friend void cima<Elemento> (const pila<Elemento>& p, Elemento& e, bool& error);
        friend bool esVacia<Elemento> (const pila<Elemento>& p);
        friend int altura<Elemento> (const pila<Elemento>& p);
        friend bool operator==<Elemento> (const pila<Elemento>& pila1, const pila<Elemento>& pila2);
        friend void liberar<Elemento> (pila<Elemento>& p);

        friend void iniciarIterador<Elemento> (pila<Elemento>& p);
        friend bool existeSiguiente<Elemento> (const pila<Elemento>& p);
        friend bool siguiente<Elemento> (pila<Elemento>& p, Elemento& e);
};

template<typename Elemento>
void crearVacia (pila<Elemento>& p) {
    p.bas = nullptr;
    p.cim = nullptr;
    p.alt = 0;
}

// puntero de la base cuidado con ant
template <typename Elemento>
void apilar (pila<Elemento>& p, const Elemento& e) {
    typename pila<Elemento>::unDato* aux = new typename pila<Elemento>::unDato;
    aux->dato = e;
    aux->sig = nullptr;
    if (esVacia(p)) {
        aux->ant = nullptr;
        p.bas = aux;
        p.cim = aux;
    } else {
        aux->ant = p.cim;
        p.cim->sig = aux;
        p.cim = aux;
        if (p.alt == 1) p.bas->sig = aux;   // sino es aux es p.cim
    }
    p.alt++;            // Altura de la pila + 1.
}

template<typename Elemento>
void desapilar (pila<Elemento>& p) {
    typename pila<Elemento>::unDato* aux;
    if (p.alt > 0) {
        aux = p.cim;
        p.cim = p.cim->ant; // Asignamos cima al anterior dato.
        delete aux;         // Liberamos la memoria donde se alamcenaba la antigua cima
        p.alt--;            // Altura de la pila - 1.
        if (p.alt == 0) {
            p.cim = nullptr;
            p.bas = nullptr;
        } else {
            p.cim->sig = nullptr;
        }
    }
}

template<typename Elemento>
void cima (const pila<Elemento>& p, Elemento& e, bool& error) {
    if (p.alt == 0) error = true;
    else {
        error = false;
        e = p.cim->dato;
    }
}

template<typename Elemento>
bool esVacia (const pila<Elemento>& p) {
    return p.alt == 0;
}

template<typename Elemento>
int altura (const pila<Elemento>& p) {
    return p.alt;
}

template<typename Elemento>
bool operator== (const pila<Elemento>& pila1, const pila<Elemento>& pila2) {
    if (pila1.alt != pila2.alt) return false;
    else {
        typename pila<Elemento>::unDato* pt1;
        typename pila<Elemento>::unDato* pt2;
        pt1 = pila1.cim;
        pt2 = pila2.cim;
        bool iguales = true;
        while (pt1 != nullptr && iguales) {
            iguales = (pt1->dato == pt2->dato);
            pt1 = pt1->ant;
            pt2 = pt2->ant;
        }
        return iguales;
    }
}

template<typename Elemento>
void liberar (pila<Elemento>& p) {
    typename pila<Elemento>::unDato* aux = new typename pila<Elemento>::unDato;
    aux = p.cim;
    while (aux != nullptr) {    // Recorremos la pila hasta la base
        p.cim = p.cim->ant;
        delete aux;
        aux = p.cim;
    }
    p.alt = 0;
    p.cim = nullptr;
    p.bas = nullptr;
}

template<typename Elemento>
void iniciarIterador (pila<Elemento>& p) {
    p.iter = p.bas;
}

template<typename Elemento>
bool existeSiguiente (const pila<Elemento>& p) {
    return p.iter != nullptr;
}

template<typename Elemento>
bool siguiente (pila<Elemento>& p, Elemento& e) {
    if (existeSiguiente(p)) {
        e = p.iter->dato;
        p.iter = p.iter->sig;
        return true;
    } else {
        return false;
    }
}

#endif