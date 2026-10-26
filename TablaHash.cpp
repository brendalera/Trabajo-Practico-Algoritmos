#include "TablaHash.h"
#include <iostream>

TablaHash::TablaHash()
    : cantidad(0), colisiones(0) {

    for (int i = 0; i < tamanio; i++) {
        tabla[i] = nullptr; //indica que esa posicion (todas porque el for recorre toda la tabla) todavia no apunta a ningun nodo
    }
}

TablaHash::~TablaHash() { //Destructor (libera la memoria)
    for (int i = 0; i < tamanio; i++) {
        Nodo* actual = tabla[i];

        while (actual != nullptr) {
            Nodo* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }
}

int TablaHash::funcionHash(const std::string& codigo) const {
    unsigned long long hash = 0;

    for (char caracter : codigo) {
        hash = hash * 31 +
               static_cast<unsigned char>(caracter);
    }

    return static_cast<int>(hash % tamanio);
}

bool TablaHash::insertar(const Estacion& estacion) {
    int posicion = funcionHash(estacion.getCodigo());
    Nodo* actual = tabla[posicion];

    // Verificamos si el codigo ya existe
    while (actual != nullptr) {
        if (actual->estacion.getCodigo() ==
            estacion.getCodigo()) {
            return false;
        }

        actual = actual->siguiente;
    }

    // Si la posicion ya tenia una estacion,
    // insertar aqui genera una colision
    if (tabla[posicion] != nullptr) {
        colisiones++;
    }

    // Creamos el nodo y lo insertamos al principio
    Nodo* nuevo = new Nodo(estacion);
    nuevo->siguiente = tabla[posicion];
    tabla[posicion] = nuevo;

    cantidad++;

    return true;
}

bool TablaHash::buscar(const std::string& codigo,
                       Estacion& resultado) const {
    int posicion = funcionHash(codigo);
    Nodo* actual = tabla[posicion];

    while (actual != nullptr) {
        if (actual->estacion.getCodigo() == codigo) {
            resultado = actual->estacion;
            return true;
        }

        actual = actual->siguiente;
    }

    return false;
}

Estacion* TablaHash::obtener(const std::string& codigo) {
    Nodo* actual = tabla[funcionHash(codigo)];

    while (actual != nullptr) {
        if (actual->estacion.getCodigo() == codigo) {
            return &actual->estacion;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}

bool TablaHash::eliminar(const std::string& codigo) {
    int posicion = funcionHash(codigo);
    Nodo* actual = tabla[posicion];
    Nodo* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->estacion.getCodigo() == codigo) {

            if (anterior == nullptr) {
                // El nodo eliminado era el primero
                tabla[posicion] = actual->siguiente;
            } else {
                // Saltamos el nodo que vamos a eliminar
                anterior->siguiente = actual->siguiente;
            }

            delete actual;
            cantidad--;

            return true;
        }

        anterior = actual;
        actual = actual->siguiente;
    }

    return false;
}

int TablaHash::getCantidad() const {
    return cantidad;
}

int TablaHash::getColisiones() const {
    return colisiones;
}

double TablaHash::factorCarga() const {
    return static_cast<double>(cantidad) / tamanio;
}

void TablaHash::mostrarTodas() const {
    for (int i = 0; i < tamanio; i++) {
        Nodo* actual = tabla[i];

        while (actual != nullptr) {
            actual->estacion.mostrar();
            std::cout << "--------------------" << std::endl;

            actual = actual->siguiente;
        }
    }
}

Estacion* TablaHash::copiarEnArreglo(int& cantidadCopiada) const {
    Estacion* arreglo = new Estacion[cantidad];
    int indice = 0;

    for (int i = 0; i < tamanio; i++) {
        Nodo* actual = tabla[i];

        while (actual != nullptr) {
            arreglo[indice++] = actual->estacion;
            actual = actual->siguiente;
        }
    }

    cantidadCopiada = indice;
    return arreglo;
}