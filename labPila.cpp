#include <iostream>
#include "pila.h"
#include "puntos2D.h"
#include <string>

using namespace std;

// void crear (puntos2D& p ,const double a, const double b, const string d);
// double suX (puntos2D& p);
// double suY (puntos2D& p);
// string suDescripcion (puntos2D& p);
// bool operator== (const puntos2D p1, const puntos2D p2);
// bool operator< (const puntos2D p1, const puntos2D p2);
// string fixCadena (double r);
// string generarCadena (puntos2D& p);

// void crearVacia (pila<Elemento>& p);                                             ||  Funciona
// void apilar (pila<Elemento>& p, const Elemento& e);                              ||  Funciona
// void desapilar (pila<Elemento>& p);                                              ||  No Funciona
// void cima (const pila<Elemento>& p, Elemento& e, bool& error);                   ||  Funciona
// bool esVacia (const pila<Elemento>& p);                                          ||  Funciona
// int altura (const pila<Elemento>& p);                                            ||  Funciona
// bool operator== (const pila<Elemento>& pila1, const pila<Elemento>& pila2);      ||  No Funciona
// void liberar (pila<Elemento>& p);                                                ||  No Funciona
// void iniciarIterador (pila<Elemento>& p);                                        ||  ¿?
// bool existeSiguiente (const pila<Elemento>& p);                                  ||  ¿?
// void siguiente (pila<Elemento>& p, Elemento& e, bool& error);                    ||  ¿?

int main() {
    int x[] = {0,1,2,3,4,5};
    int y[] = {0,0,0,0,0,0};
    pila<int> p;
    pila<int> q;
    pila<int> k;
    crearVacia(p);
    crearVacia(q);
    crearVacia(k);

    int e;
    bool error;
    bool iguales1 = (p == q);
    bool iguales2 = (p == k);


        cout << "==============================" << endl;
        cout << "VACIA: " << esVacia (p) << endl;
        cout << "==============================" << endl;
    for (int i = 0; i < 6; i++) {
        apilar (p, x[i]);
        apilar (q, x[i]);
        apilar (k, y[i]);
        cima(p, e, error);
        cout << "CIMA: " << e << endl;
        cout << "SIZE: " << altura(p) << endl;
        cout << "==============================" << endl;
    }
        cout << "VACIA: " << esVacia (p) << endl;
        cout << "==============================" << endl;
        cout << "IGUALES p Y q: " << iguales1 << " DEBERÍA SER 1" << endl;
        cout << "IGUALES p Y k: " << iguales2 << " DEBERÍA SER 0" << endl;
        cout << "==============================" << endl;
        //liberar(p);
        cout << "LIBERAR P, DEVERIA SER VACÍA" << endl;
        cout << "SIZE: " << altura(p) << endl;
        cout << "VACIA: " << esVacia (p) << endl;
        cout << "==============================" << endl;
        cout << "ITERADOR:" << endl;
        iniciarIterador(q);
        siguiente (q, e, error);
        int i=0;
    while(!error && i < 6) {
        if (e == x[i]) {
            cout << "ELEMENTO: " << e << " CORRECTO" << endl;
        } else {
            cout << "ELEMENTO: " << e << " INCORRECTO DEBERIA SER: " << x[i]<< endl;
        }
        i++;
    }
        cout << "==============================" << endl;
        cout << "DESAPILAR Q:" << endl;
    for (int i = 0; i < 6; i++) {
        desapilar(q);
        altura(q);
        cout << "SIZE: " << altura(p) << endl;
        cout << "VACIA: " << esVacia (p) << endl;
        cout << "==============================" << endl;
    }

    return 0;
}