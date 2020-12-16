#include <iostream>
#include "colecciones.h"
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
// void desapilar (pila<Elemento>& p);                                              ||  Funciona
// void cima (const pila<Elemento>& p, Elemento& e, bool& error);                   ||  Funciona
// bool esVacia (const pila<Elemento>& p);                                          ||  Funciona
// int altura (const pila<Elemento>& p);                                            ||  Funciona
// bool operator== (const pila<Elemento>& pila1, const pila<Elemento>& pila2);      ||  Funciona
// void liberar (pila<Elemento>& p);                                                ||  Funciona
// void iniciarIterador (pila<Elemento>& p);                                        ||  Funciona
// bool existeSiguiente (const pila<Elemento>& p);                                  ||  Funciona
// void siguiente (pila<Elemento>& p, Elemento& e, bool& error);                    ||  Funciona

// void crear (coleccion<Elemento>& c);                                                         ||  Funciona
// void aniadir (coleccion<Elemento>& c, const Elemento& e);                                    ||  Funciona
// bool esta (const coleccion<Elemento>& c, const Elemento& e);                                 ||  Funciona
// void obtenerUltimo (const coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo);      ||  Funciona
// void borrar (coleccion<Elemento>& c, const Elemento& e);                                     ||  
// void borrarUltimo (coleccion<Elemento>& c, const Elemento& e);                               ||
// int tamanio (const coleccion<Elemento>& c);                                                  ||  Funciona
// bool esVacia (const coleccion<Elemento>& c);                                                 ||  Funciona
// void iniciarIterador (coleccion<Elemento>& c);                                               ||
// bool existeSiguiente (const coleccion<Elemento>& c);                                         ||
// bool siguiente (coleccion<Elemento> &c, Elemento& next, bool& error);                        ||

int main() {
    int x[] = {0,1,1,3,1,5};
    int b[] = {0,1,2,3,4,5};
    int ultimo;
    coleccion<int> c;
    crear (c);
    cout << "Es vacia? " << esVacia(c) << endl;
    for(int i = 0; i < 6 ; i++) {
        aniadir (c, x[i]);
        obtenerUltimo (c, x[i], ultimo);
        cout << "===============" << endl;
        cout << "Ultimo = a: " << x[i] << " es: " << ultimo << endl;
        cout << "Tamaño c: " << to_string(tamanio(c)) << endl;
        cout << "Es vacia? " << esVacia(c) << endl;
        cout << "===============" << endl;
    }
    /*
    cout << endl;
    for(int i = 0; i < 6 ; i++) {
        cout << "===============" << endl;
        cout << "ESTA " << b[i] <<"? " << esta(c, b[i]) << endl;
        cout << "===============" << endl;
    }
    cout << endl;
    for(int i = 0; i < 6 ; i++) {
        aniadir (c, x[i]);
        borrarUltimo (c, x[i]);
        cout << "===============" << endl;
        cout << "Borrado Ultimo = a: " << x[i] << endl;
        cout << "Tamaño c: " << to_string(tamanio(c)) << endl;
        cout << "Es vacia? " << esVacia(c) << endl;
        cout << "===============" << endl;
    }*/
    /*
    int p;
    iniciarIterador (c);
    int next;
    bool error;
    siguiente (c, next, error);
    while (!error) {
        cout << next << endl;
        siguiente (c, next, error);
    }
    */


    return 0;
}