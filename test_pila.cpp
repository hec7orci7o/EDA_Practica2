#include <iostream>
#include <string.h>
#include "pila.h"
#include "puntos2D.h"

using namespace std;

int main() {
    pila<puntos2D> p;
    pila<puntos2D> p2;

    puntos2D punto;
    puntos2D puntoAUX;
    bool error;
    double x[] = {1,2,3,4,5};
    double y[] = {1,2,3,4,5};
    string d[] = {"primero","segundo","tercero","cuarto","quinto"};

    crearVacia(p);
    crearVacia(p2);
    
    for (int i = 0; i < 5; i++) {
        crear(punto, x[i], y[i], d[i]);
        apilar(p, punto);
        apilar(p2, punto);
    }
    if (p == p2) cout << "chupa pinga habi fields ";
    else cout << "chupa pinga retarder ";

    return 0;
}