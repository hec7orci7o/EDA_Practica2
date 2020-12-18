//-------------------------------------------------------------------------------------------
// File:    punto2D.cpp
// Authors: Pablo Lacueva(799134) & Hector Toral(798095)
// Date:    dic 2020
// Coms:    Practica 2 de EDA
//          Link del repositorio: https://github.com/hec7orci7o/EDA_Practica2
//-------------------------------------------------------------------------------------------

#include "puntos2D.h"

using namespace std;

// Crea un punto2D con a como coordenada x, con b como coordenada y, y con descripción d.
void crear (puntos2D& p ,const double a, const double b, const string d) {
    p.x = a;
    p.y = b;
    p.descripcion = d;
}

// Devuelve el valor de la coordenada X del punto p.
double suX (puntos2D& p) {
    return p.x;
}

// Devuelve el valor de la coordenada Y del punto p.
double suY (puntos2D& p) {
    return p.y;
}

// Devuelve la descripción del punto p.
string suDescripcion (puntos2D& p) {
    return p.descripcion;
}

// Devuelve verdad si y solo si las coordenada x de los puntos p1 y p2 tienen el mismo valor, y
// además también coinciden las coordenada y. Devuelve falso en cualquier otro caso.
bool operator== (const puntos2D p1, const puntos2D p2) {
    return (p1.x == p2.x) && (p1.y == p2.y);
}

// Devuelve verdad si y solo si la coordenada x del punto p1 es menor que la coordenada x del
// punto p2, o si las coordenadas x de ambos puntos son iguales pero, la coordenada y del punto p1
// es menor que la coordenada y del punto p2. Devuelve falso en cualquier otro caso.
bool operator< (const puntos2D p1, const puntos2D p2) {
    if (p1.x < p2.x)  return true;
    if (p1.x == p2.x) return p1.y < p2.y;
    return false;
}

// Devuelve una cadena con el valor numérico de un dato de tipo real con 2 cifras decimales.
// WARNING: Función de uso restringido, el programador no debe usarla.
string fixCadena (double r) {
    stringstream ss;
    ss << fixed << setprecision(2) << r;
    return ss.str();
}

// Devuelve una cadena con la representación alfanumérica de la información del punto p con el
// formato: primero el valor de la coordenada x, luego la cadena " ; ", luego el valor de la 
// coordenada y, luego una cadena " ; ", luego una cadena " ; ", y por último la descripción 
// del punto p.
string generarCadena (puntos2D& p) {
    string cadena = fixCadena(p.x) + " ; " + fixCadena(p.y) + " ; " + p.descripcion;
    return cadena;
}