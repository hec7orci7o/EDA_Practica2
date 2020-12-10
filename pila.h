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

//typename pila<Elemento>::unDato* aux;
//typename pila<Elemento>::unDato* aux = new typename pila<Elemento>::unDato;

template<typename Elemento> struct pila;

template<typename Elemento> void crearVacia (pila<Elemento>& p);
template<typename Elemento> void apilar (pila<Elemento>& p, const Elemento& e);
template<typename Elemento> void desapilar (pila<Elemento>& p);
template<typename Elemento> void cima (pila<Elemento>& p, Elemento& e, bool& error);
template<typename Elemento> bool esVacia (pila<Elemento>& p);
template<typename Elemento> int altura (pila<Elemento>& p);
//template<typename Elemento> void duplicar (const pila<Elemento> pilaEnt, pila<Elemento>& pilaSal);
template<typename Elemento> bool operator== (const pila<Elemento> pila1, const pila<Elemento> pila2);
template<typename Elemento> void liberar (pila<Elemento>& p);

template<typename Elemento> void iniciarIterador (pila<Elemento>& p);
template<typename Elemento> bool existeSiguiente (const pila<Elemento> p);
template<typename Elemento> void siguiente (pila<Elemento>& p, Elemento& e, bool& error);

template <typename Elemento>
struct pila {
    friend void crearVacia<Elemento> (pila<Elemento>& p);
    friend void apilar<Elemento> (pila<Elemento>& p, const Elemento& e);
    friend void desapilar<Elemento> (pila<Elemento>& p);
    friend void cima<Elemento> (pila<Elemento>& p, Elemento& e, bool& error);
    friend bool esVacia<Elemento> (pila<Elemento>& p);
    friend int altura<Elemento> (pila<Elemento>& p);
    //friend void duplicar<Elemento> (const pila<Elemento> pilaEnt, pila<Elemento>& pilaSal);
    friend bool operator==<Elemento> (const pila<Elemento> pila1, const pila<Elemento> pila2);
    friend void liberar<Elemento> (pila<Elemento>& p);

    friend void iniciarIterador<Elemento> (pila<Elemento>& p);
    friend bool existeSiguiente<Elemento> (const pila<Elemento> p);
    friend void siguiente<Elemento> (pila<Elemento>& p, Elemento& e, bool& error);
    private:
        struct unDato {
            Elemento dato;
            unDato* sig;
        };
        unDato* cim;
        int alt;
        unDato* iter;
};

template<typename Elemento>
void crearVacia (pila<Elemento>& p) {
    p.cim = nullptr;
    p.alt = 0;
}

template <typename Elemento>
void apilar(pila<Elemento>& p, const Elemento& e) {
    typename pila<Elemento>::unDato* aux;
    aux = new typename pila<Elemento>::unDato;
    aux->dato = e;
    aux->sig = p.cim;
    p.cim = aux;
    p.alt++;
}

template<typename Elemento>
void desapilar (pila<Elemento>& p) {
    typename pila<Elemento>::unDato* aux;
    if (p.alt != 0) {
        aux = p.cim;
        p.cim = p.cim->sig;
        delete aux;
        p.alt--;
    }
}

template<typename Elemento>
void cima (pila<Elemento>& p, Elemento& e, bool& error) {
    if (p.alt == 0) error = true;
    else {
        error = false;
        e = p.cim->dato;
    }
}

template<typename Elemento>
bool esVacia (pila<Elemento>& p) {
    return p.alt == 0;
}

template<typename Elemento>
int altura (pila<Elemento>& p) {
    return p.alt;
}

template<typename Elemento>
void duplicar (const pila<Elemento> pilaEnt, pila<Elemento>& pilaSal) {
    if (esVacia(pilaEnt)) {
        crearVacia(pilaSal);
    } else {
        typename pila<Elemento>::unDato* ptEnt = pilaEnt.cim;
        typename pila<Elemento>::unDato* ptSal = new typename pila<Elemento>::unDato;
        pilaSal.cim = ptSal;
        pilaSal.cim->sig = nullptr;
        ptEnt = ptEnt->sig;
        while (ptEnt != nullptr) {
            typename pila<Elemento>::unDato* aux = new typename pila<Elemento>::unDato;
            ptSal->sig = aux;
            aux->dato = ptEnt->dato;
            ptSal = ptSal->sig;
            ptEnt = ptEnt->sig;
        }
        ptSal->sig = nullptr;
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
            pt1 = pt1->sig;
            pt2 = pt2->sig;
        }
        return iguales;
    }
}

template<typename Elemento>
void liberar (pila<Elemento>& p) {
    typename pila<Elemento>::unDato* aux = new typename pila<Elemento>::unDato;
    aux = p.cim;
    while (aux != nullptr) {
        p.cim = p.cim->sig;
        delete aux;
        aux = p.cim;
    }
    p.alt = 0;
}

template<typename Elemento>
void iniciarIterador (pila<Elemento>& p) {
    p.iter = p.cim;
}

template<typename Elemento>
bool existeSiguiente (const pila<Elemento> p) {
    return p.iter != nullptr;
}

template<typename Elemento>
void siguiente (pila<Elemento>& p, Elemento& e, bool& error) {
    if (existeSiguiente(p)) {
        error = false;
        e = p.iter->dato;
        p.iter = p.iter->sig;
    } else {
        error = true;
    }
}

#endif