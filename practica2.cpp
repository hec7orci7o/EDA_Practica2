//-------------------------------------------------------------------------------------------
// File:   practica2.cpp
// Authors: Pablo Lacueva(799134) & Hector Toral(798095)
// Date:   dic 2020
// Coms:   Practica 2 de EDA
//         Compilar mediante: make
//         Limpiar  mediante: make clean
//         Link del repositorio: https://github.com/hec7orci7o/EDA_Practica2
//-------------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "puntos2D.h"
#include "colecciones.h"

using namespace std;

// DATOS CTEs
const string Fentrada = "entrada.txt";
const string Fsalida  = "salida.txt";

// DEF
// Selecciona la instrucción a ejecutar.
void selecINST(ifstream& f, ofstream& g, coleccion<puntos2D>& c, const string INST);
// Añade un elemento <puntos2D> a la colección <c>.
void A (ifstream& f, ofstream& g, coleccion<puntos2D>& c);
// Comprueba que el elemento <puntos2D> introducido esta en la colección <c>.
void E (ifstream& f, ofstream& g, coleccion<puntos2D>& c);
// Obtiene el último elemento <puntos2D> igual al introducido.
void OU (ifstream& f, ofstream& g, coleccion<puntos2D>& c);
// Borra el último elemento <puntos2D> igual al introducido de la colección <c>.
void BU (ifstream& f, ofstream& g, coleccion<puntos2D>& c);
// Borra todos los elementos <puntos2D> iguales al introducido de la colección <c>.
void B (ifstream& f, ofstream& g, coleccion<puntos2D>& c);
// Muestra todos los elementos <puntos2D> pertenecientes a la colección <c> iguales al introducido.
void LI (ifstream& f, ofstream& g, coleccion<puntos2D>& c);
// Lista todos los elementos de la colección.
void LT (ifstream& f, ofstream& g, coleccion<puntos2D>& c);

int main() {
    coleccion<puntos2D> c;

    ifstream f(Fentrada);
    ofstream g(Fsalida);
    if (f.is_open() && g.is_open()) {
        crear(c);
        string INST;
        f >> INST;
        while (!f.eof()) {
            selecINST(f, g, c, INST);
            f >> INST;
        }
        f.close();
        g.close();
        return true;
    } else {
        cerr << "ERROR al abrir uno de los archivos.";
        return false;
    }

    return 0;
}

void selecINST(ifstream& f, ofstream& g, coleccion<puntos2D>& c, const string INST) {
    if (INST ==  "A")  A(f, g, c);
    if (INST ==  "E")  E(f, g, c);
    if (INST == "OU") OU(f, g, c);
    if (INST == "BU") BU(f, g, c);
    if (INST ==  "B")  B(f, g, c);
    if (INST == "LI") LI(f, g, c);
    if (INST == "LT") LT(f, g, c);
}

// Pre:  Punto2D{Coord_X,Coord_Y,Descripcion}
// Post: INTRODUCIDO: Coord_X ; Coord_Y ; Descripcion
void A (ifstream& f, ofstream& g, coleccion<puntos2D>& c) {
    puntos2D p;
    double x, y;
    string d;

    f >> x;
    f >> y;
    f >> d;

    crear(p, x, y, d);
    aniadir(c, p);

    g << "INTRODUCIDO: " << generarCadena(p) << endl;
}

// Pre:  Coord_X,Coord_Y
// Post:
//  BUSQUEDA CON EXITO: Coord_X ; Coord_Y
//  BUSQUEDA SIN EXITO: Coord_X ; Coord_Y
void E (ifstream& f, ofstream& g, coleccion<puntos2D>& c) {
    puntos2D p;
    double x, y;
    f >> x;
    f >> y;
    crear(p, x, y, "");
    if (esta(c, p)) {
        g << "BUSQUEDA CON EXITO: " << fixCadena(suX(p)) << " ; " << fixCadena(suY(p)) << endl;
    } else {
        g << "BUSQUEDA SIN EXITO: " << fixCadena(suX(p)) << " ; " << fixCadena(suY(p)) << endl;
    }
}

// Pre:  Coord_X,Coord_Y
// Post:
//  LOCALIZADO CON EXITO: Coord_X ; Coord_Y
//  NO LOCALIZADO: Coord_X ; Coord_Y
void OU (ifstream& f, ofstream& g, coleccion<puntos2D>& c) {
    puntos2D pF, pI;
    double x, y;
    f >> x;
    f >> y;
    crear(pF, x, y, "");
    if (obtenerUltimo(c,pF,pI)) {
        g << "LOCALIZADO CON EXITO: " << generarCadena(pI) << endl;
    } else {
        g << "NO LOCALIZADO: " << fixCadena(suX(pF)) << " ; " << fixCadena(suY(pF)) << endl;
    }
}

// Pre:  Coord_X,Coord_Y
// Post:
//  BORRADO ULTIMO DE: Coord_X ; Coord_Y
//  NO BORRABLE: Coord_X ; Coord_Y
void BU (ifstream& f, ofstream& g, coleccion<puntos2D>& c) {
    puntos2D p;
    double x, y;
    f >> x;
    f >> y;
    crear(p, x, y, "");
    if (borrarUltimo (c, p)) {
        g << "BORRADO ULTIMO DE: " << fixCadena(suX(p)) << " ; " << fixCadena(suY(p)) << endl;
    } else {
        g << "NO BORRABLE: " << fixCadena(suX(p)) << " ; " << fixCadena(suY(p)) << endl;
    }
}

// Pre:  Coord_X,Coord_Y
// Post:
//  ELIMINADO CON EXITO: Coord_X ; Coord_Y
//  NINGUNO PARA ELIMINAR: Coord_X ; Coord_Y
void B (ifstream& f, ofstream& g, coleccion<puntos2D>& c) {
    puntos2D p;
    double x, y;
    f >> x;
    f >> y;
    crear(p, x, y, "");
    if (borrar(c, p)) {
        g << "ELIMINADO CON EXITO: " << fixCadena(suX(p)) << " ; " << fixCadena(suY(p)) << endl;
    } else {
        g << "NINGUNO PARA ELIMINAR: " << fixCadena(suX(p)) << " ; " << fixCadena(suY(p)) << endl;
    }
}

// Pre:  Coord_X,Coord_Y
// Post:
//  -----
//  Coord_Xi ; Coord_Yi ; Descripcion_i
//  -----TOTAL n IGUALES A: Coord_X ; Coord_Y
void LI (ifstream& f, ofstream& g, coleccion<puntos2D>& c) {
    puntos2D pF, pi;    // pF = puntoFijo; pi = puntoIterativo
    double x, y;
    int TOTAL = 0;
    f >> x;
    f >> y;
    crear(pF, x, y, "");

    g << "-----" << endl;
    iniciarIterador(c);
    while (siguiente(c, pi)) {
        if (pi == pF) {
            TOTAL++;
            g << generarCadena(pi) << endl;
        }
    }
    g << "-----TOTAL " << TOTAL << " IGUALES A: " << fixCadena(suX(pF)) << " ; " << fixCadena(suY(pF)) << endl;
}

// Pre:  Coleccion de puntos2D
// Post:
//  -----TOTAL: <c.total>
//  Coord_Xi ; Coord_Yi ; Descripcion_i
//  -----
void LT (ifstream& f, ofstream& g, coleccion<puntos2D>& c) {
    puntos2D p;
    g << "-----TOTAL: " << tamanio(c) << endl;
    iniciarIterador (c);
    while (siguiente(c,p)) {
        g << generarCadena(p) << endl;
    }
    g << "-----" << endl;
}