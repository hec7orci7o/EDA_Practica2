#include <iostream>
#include <string.h>
#include "puntos2D.h"
#include "colecciones.h"

using namespace std;

int main() {
    puntos2D e;
    coleccion<puntos2D> c;
    int x[] = {0,1,7,5,4,3, -1};
    int y[] = {0,1,7,5,4,3, -1};
    string d[] = {"raiz","primeroDerecha","SegundoDerecha","dcha-PrimeroIzda","SedundoIzda", "TerceroIzda", "..."};
    crear(c);   // crear coleccion

    aniadir(c, , e);
    cout << esVacia(c);
    for (int i = 0; i < 7; i++) {
        crear(e , x[i], y[i], d[i]);
    }
    cout << esVacia(c);
    

    return 0;
}