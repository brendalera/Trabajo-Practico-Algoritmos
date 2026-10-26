#ifndef COLA_ESPERA_H
#define COLA_ESPERA_H

#include <iostream>
#include <string>

// Cola FIFO de usuarios (DNI) esperando una bici. Lista enlazada con
// puntero al frente y al final, asi encolar y desencolar son O(1).
class ColaEspera {
private:
    struct Nodo {
        std::string dni;
        Nodo* siguiente;

        Nodo(const std::string& dni) : dni(dni), siguiente(nullptr) {
        }
    };

    Nodo* frente;
    Nodo* fin;
    int cantidad;

public:
    ColaEspera() : frente(nullptr), fin(nullptr), cantidad(0) {
    }

    ~ColaEspera() {
        Nodo* actual = frente;

        while (actual != nullptr) {
            Nodo* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    // evitamos copias superficiales de los punteros
    ColaEspera(const ColaEspera&) = delete;
    ColaEspera& operator=(const ColaEspera&) = delete;

    // Devuelve la posicion que ocupa el usuario en la cola (1 = primero)
    int encolar(const std::string& dni) {
        Nodo* nuevo = new Nodo(dni);

        if (fin == nullptr) {
            frente = nuevo;
        } else {
            fin->siguiente = nuevo;
        }

        fin = nuevo;
        cantidad++;

        return cantidad;
    }

    // Saca al primero de la cola. Devuelve false si estaba vacia.
    bool desencolar(std::string& dni) {
        if (frente == nullptr) {
            return false;
        }

        Nodo* primero = frente;
        dni = primero->dni;
        frente = primero->siguiente;

        if (frente == nullptr) {
            fin = nullptr;
        }

        delete primero;
        cantidad--;

        return true;
    }

    bool estaVacia() const {
        return frente == nullptr;
    }

    int getCantidad() const {
        return cantidad;
    }

    void mostrar() const {
        int posicion = 1;

        for (const Nodo* actual = frente; actual != nullptr; actual = actual->siguiente) {
            std::cout << posicion++ << ". DNI " << actual->dni << std::endl;
        }
    }
};

#endif