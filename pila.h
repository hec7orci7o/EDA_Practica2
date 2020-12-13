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
template<typename Elemento> void crearVacia (const pila<Elemento>& p);

// Devuelve la pila resultante de añádir <e> a <p>.
template<typename Elemento> void apilar (const pila<Elemento>& p, const Elemento& e);

// Si p es no vacia, devuelve la pila resultante de eliminar de <p>
// el último elemento que fue apilado. Si <p> es vacía, la deja igual.
template<typename Elemento> void desapilar (const pila<Elemento>& p);

// Si <p> es vacía, error toma el valor verdad y se deja <e> indefinido.
// si <p> no es vacia, error toma el valor falso y <e> toma el valor de la cima de <p>.
template<typename Elemento> void cima (const pila<Elemento> p, Elemento& e, bool& error);

// Devuelve verdad si y solo si <p> no tiene elementos.
template<typename Elemento> bool esVacia (const pila<Elemento> p);

// Devuelve el número de elementos de <p>, 0 si no tiene elementos.
template<typename Elemento> int altura (const pila<Elemento> p);

// Hace una copia en pilaSal de la pila almacenada en pilaEnt.
template<typename Elemento> void duplicar (const pila<Elemento> pilaEnt, const pila<Elemento>& pilaSal);

// Devuelve verdad si y solo si pila1 y pila2 almacenan la misma pila.
template<typename Elemento> bool operator== (const pila<Elemento> pila1, const pila<Elemento> pila2);

// Devuelve la pila vacía, liberando previamente toda la memoria que ocupa la pila de entrada <p>.
template<typename Elemento> void liberar (const pila<Elemento>& p);

// Prepara el iterador para que el siguiente elemento a visitar sea la cima de la pila <p>,
// si existe(situacion de no haber visitado ningun elemento).
template<typename Elemento> void iniciarIterador (const pila<Elemento>& p);

// Devuelve falso si ya se han visitado todos los elementos de <p>.
// Devuelve verdad en caso contrario.
template<typename Elemento> bool existeSiguiente (const pila<Elemento> p);

// Implementa las operaciones "siguiente" y "avanza" de la especificación, es decir:
// Si existeSiguiente(p), error toma el valor falso, <e> toma el valor del siguiente
// elemento de la pila, y se avanza el iterador al elemento siguiente de la pila.
// Si no existeSiguiente(p), error toma el valor verdad, <e> queda indefinido y <p> queda como estaba.
template<typename Elemento> void siguiente (const pila<Elemento>& p, Elemento& e, bool& error);

template <typename Elemento>
struct pila {
    friend void crearVacia<Elemento> (const pila<Elemento>& p);
    friend void apilar<Elemento> (const pila<Elemento>& p, const Elemento& e);
    friend void desapilar<Elemento> (const pila<Elemento>& p);
    friend void cima<Elemento> (const pila<Elemento> p, Elemento& e, bool& error);
    friend bool esVacia<Elemento> (const pila<Elemento> p);
    friend int altura<Elemento> (const pila<Elemento> p);
    friend void duplicar<Elemento> (const pila<Elemento> pilaEnt, const pila<Elemento>& pilaSal);
    friend bool operator==<Elemento> (const pila<Elemento> pila1, const pila<Elemento> pila2);
    friend void liberar<Elemento> (const pila<Elemento>& p);

    friend void iniciarIterador<Elemento> (const pila<Elemento>& p);
    friend bool existeSiguiente<Elemento> (const pila<Elemento> p);
    friend void siguiente<Elemento> (const pila<Elemento>& p, Elemento& e, bool& error);
    private:
        struct unDato {
            Elemento dato;  // dato de tipo <Elemento>. <Elemento> es un tipo generico
            unDato* sig;    // puntero que apunta a la posición del dato siguiente. Caso de la cima = nullptr.
            unDato* ant;    // puntero que apunta a la posición del dato anterior.  Caso de la base = nullptr.
        };
        unDato* cim;
        unDato* iter;
        int alt;
};

template<typename Elemento>
void crearVacia (const pila<Elemento>& p) {
    p.cim = nullptr;
    p.alt = 0;
}

template <typename Elemento>
void apilar(const pila<Elemento>& p, const Elemento& e) {
    typename pila<Elemento>::unDato* aux = new typename pila<Elemento>::unDato;
    aux = p.cim;    // Guardamos la cima anterior
    aux->sig = p.cim;       // La posición siguiente de la antigua cima, apunta al siguiente elemento 
    p.cim->dato = e;
    p.cim->sig  = nullptr;  // La posición del nuevo elemento esta todavia sin precisar.
    p.cim->ant  = aux;      // La posición del anterior elemento es la cima antigua.
    p.alt++;                // Altura de la pila + 1.
}

template<typename Elemento>
void desapilar (const pila<Elemento>& p) {
    typename pila<Elemento>::unDato* aux = new typename pila<Elemento>::unDato;;
    if (p.alt != 0) {
        aux = p.cim;
        p.cim = p.cim->ant; // Asignamos cima al anterior dato.
        delete aux;         // Liberamos la memoria donde se alamcenaba la antigua cima
        p.alt--;            // Altura de la pila - 1.
    }
}

template<typename Elemento>
void cima (const pila<Elemento> p, Elemento& e, bool& error) {
    if (p.alt == 0) error = true;
    else {
        error = false;
        e = p.cim->dato;
    }
}

template<typename Elemento>
bool esVacia (const pila<Elemento> p) {
    return p.alt == 0;
}

template<typename Elemento>
int altura (const pila<Elemento> p) {
    return p.alt;
}

template<typename Elemento>
void duplicar (const pila<Elemento> pilaEnt, const pila<Elemento>& pilaSal) {
    if (esVacia(pilaEnt)) {
        crearVacia(pilaSal);
    } else {
        typename pila<Elemento>::unDato* ptEnt;
        typename pila<Elemento>::unDato* ptSal;
        ptEnt = pilaEnt.cim;    // ptEnt apunta a los datos de pilaEnt.cim: {ptEnt->e, ptEnt->sig, ptEnt->ant}
        
        pilaSal.cim = ptSal;
        pilaSal.cim->sig = nullptr;
        pilaSal.cim->ant = nullptr;

        ptEnt = ptEnt->ant;
        while (ptEnt != nullptr) {
            typename pila<Elemento>::unDato* aux = new typename pila<Elemento>::Nodo*;
            // Actualizamos ptSal
            ptSal->ant = aux ;      // Creamos un "nodo" anterior para la pila.
            aux->sig   = ptSal;     // Ese "nodo" apunta a la cima como elemento / nodo siguiente. 
            aux->valor = ptEnt->valor;
            // Avanzamos hacia la base de la pila.
            ptEnt = ptEnt->ant;
            ptSal = ptSal->ant;
        }
        ptSal->ant = nullptr;
        pilaSal.alt = pilaEnt.alt;
    }
}

template<typename Elemento>
bool operator== (const pila<Elemento> pila1, const pila<Elemento> pila2) {
    if (pila1.alt != pila2.alt) return false;
    else {
        typename pila<Elemento>::unDato* pt1;
        typename pila<Elemento>::unDato* pt2;
        pt1 = pila1.cim;
        pt2 = pila2.cim;
        bool iguales = true;
        while (pt1 != nullptr && iguales) {
            iguales = pt1->dato == pt2->dato;
            pt1 = pt1->ant; // Recorremos la pila hacia abajo
            pt2 = pt2->ant; // Nota: Si hacemos ptX = ptX->sig iriamos a nullptr pues estamos en la cima.
        }
        return iguales;
    }
}

template<typename Elemento>
void liberar (const pila<Elemento>& p) {
    typename pila<Elemento>::unDato* aux = new typename pila<Elemento>::unDato;
    aux = p.cim;
    while (aux != nullptr) {    // Recorremos la pila hasta la base
        p.cim = p.cim->ant;
        delete aux;
        aux = p.cim;
    }
    p.alt = 0;
}

template<typename Elemento>
void iniciarIterador (const pila<Elemento>& p) {
    p.iter = p.cim;
}

template<typename Elemento>
bool existeSiguiente (const pila<Elemento> p) {
    return p.iter != nullptr;
}

template<typename Elemento>
void siguiente (const pila<Elemento>& p, Elemento& e, bool& error) {
    if (existeSiguiente(p)) {
        error = false;
        e = p.iter->dato;
        p.iter = p.iter->ant;
    } else {
        error = true;
    }
}

#endif