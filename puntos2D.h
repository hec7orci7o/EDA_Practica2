//-------------------------------------------------------------------------------------------
// File:    puntos2D.h
// Authors: Pablo Lacueva(799134) & Hector Toral(798095)
// Date:    dic 2020
// Coms:    Practica 2 de EDA
//          Link del repositorio: https://github.com/hec7orci7o/EDA_Practica2
//-------------------------------------------------------------------------------------------

#ifndef PUNTOS2D_H
#define PUNTOS2D_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

// Los valores del TAD representan puntos de dos dimensiones comentados con una descripción.
// Cada punto tiene sus coordenadas X e Y (numeros reales) y una descripción (cadena). Para
// comparar y ordenar puntos2D se utilizan unicamente los valores de sus coordenadas:
// Primero el de la X y luego el de la Y.
struct puntos2D;

// Crea un punto2D con a como coordenada x, con b como coordenada y, y con descripción d.
void crear (puntos2D& p ,const double a, const double b, const string d);

// Devuelve el valor de la coordenada X del punto p.
double suX (puntos2D& p);

// Devuelve el valor de la coordenada Y del punto p.
double suY (puntos2D& p);

// Devuelve la descripción del punto p.
string suDescripcion (puntos2D& p);

// Devuelve verdad si y solo si las coordenada x de los puntos p1 y p2 tienen el mismo valor, y
// además también coinciden las coordenada y. Devuelve falso en cualquier otro caso.
bool operator== (const puntos2D p1, const puntos2D p2);

// Devuelve verdad si y solo si la coordenada x del punto p1 es menor que la coordenada x del
// punto p2, o si las coordenadas x de ambos puntos son iguales pero, la coordenada y del punto p1
// es menor que la coordenada y del punto p2. Devuelve falso en cualquier otro caso.
bool operator< (const puntos2D p1, const puntos2D p2);

// Devuelve una cadena con el valor numérico de un dato de tipo real con 2 cifras decimales.
// WARNING: Función de uso restringido, el programador no debe usarla.
string fixCadena (double r);

// Devuelve una cadena con la representación alfanumérica de la información del punto p con el
// formato: primero el valor de la coordenada x, luego la cadena " ; ", luego el valor de la
// coordenada y, luego una cadena " ; ", luego una cadena " ; ", y por último la descripción
// del punto p.
string generarCadena (puntos2D& p);

struct puntos2D {
    friend void crear (puntos2D& p ,const double a, const double b, const string d);
    friend double suX (puntos2D& p);
    friend double suY (puntos2D& p);
    friend string suDescripcion (puntos2D& p);
    friend bool operator== (const puntos2D p1, const puntos2D p2);
    friend bool operator< (const puntos2D p1, const puntos2D p2);
    friend string generarCadena (puntos2D& p);
    private:
        double x;
        double y;
        string descripcion;
};

#endif