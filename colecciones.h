//-------------------------------------------------------------------------------------------
// File:    colecciones.h
// Authors: Pablo Lacueva(799134) & Hector Toral(798095)
// Date:    nov 2020
// Coms:    Practica 1 de EDA
//          Link del repositorio: https://github.com/hec7orci7o/EDA_Practica1
//-------------------------------------------------------------------------------------------

#ifndef COLECCIONES_H
#define COLECCIONES_H

#include <iostream>

using namespace std;

// IMPORTANTE: El typename Elemento deberá tener sobrecargado los operadores "==" y "<"

// El TAD <coleccion> representa colecciones de elementos ordenados de menor a mayor, en las que
// puede haber elementos "iguales".
// Los elementos iguales se mantendrán ordenados según su orden de incorporación a la colección.
template<typename Elemento> struct coleccion;

// Crea una colección vacia sin elementos.
template<typename Elemento> void crear (coleccion<Elemento>& c);

// Devuelve la colección resultante de añadir el elemento <e> a la colección <c>.
// RECORDAR: <c> esta ordenada de menor -> mayor.
// Si en <c> ya había algún elemento igual a <e>, este quedará como el último de todos los iguales.
template<typename Elemento> bool aniadir (coleccion<Elemento>& c, const Elemento e);

// Devuelve "TRUE" si y solo si en <c> hay algún elemento igual a <e>.
template<typename Elemento> bool esta (const coleccion<Elemento>& c, const Elemento e);

// Si en <c> hay algún elemento igual a <e>, devuelve el último elemento igual a <e> que fue
// añadido a la colección <c>.
// PARCIAL: Operación no definida si <e> no esta en c
template<typename Elemento> bool obtenerUltimo (const coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo);

// Si en <c> hay algún elemento igual a <e>, devuelve la colección resultante de borrar de <c>
// todos los elementos iguales a <e>.
// En caso contrario, devuelve una colección igual a <c>.
template<typename Elemento> bool borrar (coleccion<Elemento>& c, const Elemento e);

// Si en <c> hay algún elemento igual a <e>, devuelve la colección resultante de borrar de <c>
// el último elemento igual a <e> que fue añadido a la colección.
// En caso contrario devuelve una colección igual a <c>.
template<typename Elemento> bool borrarUltimo (coleccion<Elemento>& c, const Elemento e);

// Devuelve el número total de elementos de la colección.
template<typename Elemento> int tamanio (const coleccion<Elemento>& c);

// Devuelve "TRUE" si y solo si <c> no tiene ningún elemento.
template<typename Elemento> bool esVacia (const coleccion<Elemento>&c);

// Inicializa el iterador para recorrer los elementos de la colección <c>, de forma que el
// siguiente elemento a visitar sea el primero.
template<typename Elemento> void iniciarIterador (coleccion<Elemento>& c);

// Devuelve "TRUE" si queda algún elemento por visitar con el iterador de la colección <c>,
// devuelve "FALSE" si ya se ha visitado el último elemento.
template<typename Elemento> bool existeSiguiente (const coleccion<Elemento>& c);

// Devuelve el siguiente elemento a visitar con el iterador de la colección <c> y avanza el iterador
// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> bool siguiente (coleccion<Elemento> &c, Elemento& next);

template <typename Elemento>
struct coleccion {
    friend void crear<Elemento> (coleccion<Elemento>& c);
    friend bool aniadir<Elemento> (coleccion<Elemento>& c, const Elemento e);
    friend bool esta<Elemento> (const coleccion<Elemento>& c, const Elemento e);
    friend bool obtenerUltimo<Elemento> (const coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo);
    friend bool borrar<Elemento> (coleccion<Elemento>& c, const Elemento e);
    friend bool borrarUltimo<Elemento> (coleccion<Elemento>& c, const Elemento e);
    friend int  tamanio<Elemento> (const coleccion<Elemento>& c);
    friend bool esVacia<Elemento> (const coleccion<Elemento>&c);

    friend void iniciarIterador<Elemento> (coleccion<Elemento>& c);
    friend bool existeSiguiente<Elemento> (const coleccion<Elemento>& c);
    friend bool siguiente<Elemento> (coleccion<Elemento> &c, Elemento& next);
    private:
        struct Nodo {
            Elemento e;
            Nodo* siguiente;
        };
        Nodo* primerNodo;
        int   total;
        Nodo* iterador;
};

template<typename Elemento>
void crear (coleccion<Elemento>& c) {
    c.total = 0;
    c.primerNodo = nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool aniadir (coleccion<Elemento>& c, const Elemento e) {
    typename coleccion<Elemento>::Nodo* nuevo = new typename coleccion<Elemento>::Nodo;
    nuevo->e = e;

    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        nuevo->siguiente = nullptr;
        c.primerNodo = nuevo;
        c.total++;
        return true;        // Añadimos el primer elemento.
    } else {            // Caso 1: La colecccion NO es vacia.
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;
        if (e < current->e) {   // Caso 1.1: El elemento <e> es EXACTAMENTE el primer elemento.
            c.primerNodo = nuevo;
            nuevo->siguiente = current;
            c.total++;
            return true;
        } else {
            while (next != nullptr) {    // Caso 1.2: El elemento <e> puede estar en este rango [1..n-1]; next = nullptr si n.
                if ((current->e < e || current->e == e) && e < next->e) {   // Caso 1.2.1: current->e < e && e < next->e => Elemento <e> no esta en <c>.
                    current->siguiente = nuevo;                             // Caso 1.2.2: current->e == e && e < next->e => Elemento <e> esta en <c>.
                    nuevo->siguiente = next;
                    c.total++;
                    return true;
                }   // Si no hemos llegado al lugar de insercion iteramos.
                current = current->siguiente;
                next = next->siguiente;
            }   // Caso 1.3: El elemento <e> esta en n. (next->siguiente = nullptr)
            current->siguiente = nuevo;
            c.total++;
            nuevo->siguiente = nullptr;
            return true;
        }
        return false;
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool esta (const coleccion<Elemento>& c, const Elemento e) {
    typename coleccion<Elemento>::Nodo* buscador;
    buscador = c.primerNodo;
    while(buscador->siguiente != nullptr) { // Rango = [0..n-1]
        if (buscador->e == e) return true;  // Caso 0: Elemento <e> esta en la posicion i.
        buscador = buscador->siguiente;
    }
    if (buscador->e == e) return true;      // Caso 1: Elemento <e> esta en la posicion n.
    return false;
}

// PARCIAL: Operación no definida si <e> no esta en c
template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool obtenerUltimo (const coleccion<Elemento>& c, const Elemento& e, Elemento& ultimo) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede obtener ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente; // next apunta a un <e> por delante de current: <current = @[i]> <next = @[i+1]> desde un i = primerNodo;

        while(next != nullptr) {
            if (current->e == e && e < next->e) { // Caso 1: <e> esta en el rango[0..n-1]; n = @next := nullptr
                ultimo = current->e;
                return true;
            } else {
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: <e> esta en @current; @current->siguiente := nullptr
            ultimo = current->e;     //    Es decir: <e> es el ultimo elemento.
            return true;
        }
        return false;   // Caso 3: <e> No esta en la coleccion.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrar (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse ninguno.
    } else {
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        current = c.primerNodo;
        typename coleccion<Elemento>::Nodo* basura;

        if (current->e == e) {  // Caso 1: La coleccion <c> tiene como primer elemento el <e>.
            while (current != nullptr && current->e == e) {
                c.total--;
                basura = current;
                current = current->siguiente;
                delete basura;
            }
            if (esVacia(c)) {
                c.primerNodo = nullptr;
                return true;
            }
            c.primerNodo = current;
            return true;
        } else {
            typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
            next = c.primerNodo;
            next = next->siguiente;

            while (next != nullptr) {    // Caso 2: El elemento <e> se encuentra en el rango[1..n-1];  n = @next := nullptr
                if (!(current->e == e) && next->e == e) {   // Avanzamos hasta detectar un <ei> == e;
                                                            // current->e < e. Es decir @current es el anterior al primer @e.
                    while (next != nullptr) {    // El elemento <e> se encuentra en el rango[i..n-1];  n = @next := nullptr
                        if (!(next->e == e)) {                  // Cuando next->e vuelva a ser distinto del elemento <e>: recorridos todos los <e>
                            current->siguiente = next;
                            return true;
                        } else {
                            --c.total;
                            basura = next;
                            next = next->siguiente;
                            delete basura;
                        }
                    }
                } else {         // Mientras no detectemos un <e> avanzamos en la coleccion.
                    current = current->siguiente;
                    next = next->siguiente;
                }
            }
            // Caso 3: El elemento <e> NO se encuentra en el rango[i..n-1]; minimo i = 1; n = @next := nullptr
            current->siguiente = nullptr;
            return false;
        }
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(n) = lineal al tamaño de la colección.
bool borrarUltimo (coleccion<Elemento>& c, const Elemento e) {
    if (esVacia(c)) {   // Caso 0: La colecccion es vacia.
        return false;       // No puede borrarse nada.
    } else {
        typename coleccion<Elemento>::Nodo* previous = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* current = new typename coleccion<Elemento>::Nodo;
        typename coleccion<Elemento>::Nodo* next = new typename coleccion<Elemento>::Nodo;
        previous = c.primerNodo;
        current = c.primerNodo;
        next = c.primerNodo;
        next = next->siguiente;

        while (next != nullptr) {    // Caso 1: cuando la colección <c> tenga 2 o más elementos.
            if (next->e == e) {
                // split = @previous queda como marca a enlazar con el @next para realizar el borrado.
                // split = @current apunta al elemento <e> que se quiere borrar.
                current = current->siguiente;
                next = next->siguiente;
                while (next != nullptr) { // Buscamos el ultimo <ei> == <e> en el rango[i..n-1]; min i = @primer_e; n = @next := nullptr
                    if (current->e == e && e < next->e) {   // Si encontramos un <ei> != <e> en rango[i..n-1] borramos último.
                        c.total--;
                        previous->siguiente = next;
                        delete current;
                        return true;
                    } else {    // Avanzamos mientras no se encuentre un <ei> != <e>
                        previous = previous->siguiente;
                        current = current->siguiente;
                        next = next->siguiente;
                    }
                }
            } else {    // Avanzamos hasta detectar un <ei> == <e>
                previous = previous->siguiente;
                current = current->siguiente;
                next = next->siguiente;
            }
        }
        if (current->e == e) {  // Caso 2: cuando la coleccion <c> tenga 1 o mas elementos.
            c.total--;
            previous->siguiente = nullptr;
            delete current;
            return true;            // Borra el ultimo <ei> o el unico <ei> en el caso de que c.total:=1
        }
        return false;   // No existe un <ei> para borrar.
    }
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
int tamanio (const coleccion<Elemento>& c) {
    return c.total;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool esVacia (const coleccion<Elemento>&c) {
    return c.primerNodo == nullptr;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
void iniciarIterador (coleccion<Elemento>& c) {
    c.iterador = c.primerNodo;
}

template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool existeSiguiente (const coleccion<Elemento>& c) {
    return c.iterador != nullptr;
}

// PARCIAL: Operación no definida si no quedan elementos por visitar.
template<typename Elemento> // Coste Algorítmico Peor: O(1) = constante.
bool siguiente (coleccion<Elemento> &c, Elemento& next) {
    if (existeSiguiente(c)) {
        next = c.iterador->e;
        c.iterador = c.iterador->siguiente;
        return true;
    }
    return false;
}

#endif
