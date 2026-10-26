#ifndef TABLA_HASH_H
#define TABLA_HASH_H

#include "Estacion.h"
#include <string>

class TablaHash {
private:
    static const int tamanio = 101; //La tabla va a tener 101 posiciones (del 0 al 100)

    // estructura del nodo de nuestra lista enlazada
    struct Nodo {
        Estacion estacion;
        Nodo* siguiente;

        Nodo(const Estacion& estacion)
            : estacion(estacion), siguiente(nullptr) {
        }
    };

    // Cada posicion apunta al inicio de una lista
    Nodo* tabla[tamanio];

    int cantidad; //cuantas estaciones hay almacenadas
    int colisiones; //contador de colisiones
    int funcionHash(const std::string& codigo) const; //transforma el codigo de la estacion en una posicion de la tabla

public:
    TablaHash();
    ~TablaHash(); //es el destructor, sirve para liberar la memoria reservada con new

    // evitamos copias superficiales de los punteros
    TablaHash(const TablaHash&) = delete;
    TablaHash& operator=(const TablaHash&) = delete;
    
    int getColisiones() const;

    bool insertar(const Estacion& estacion);
    bool buscar(const std::string& codigo, Estacion& resultado) const;
    bool eliminar(const std::string& codigo);

    // Devuelve un puntero a la estacion guardada (nullptr si no existe),
    // para poder modificarla sin copiarla
    Estacion* obtener(const std::string& codigo);

    int getCantidad() const;
    double factorCarga() const; //calcula la cantidad de estaciones dividida por el tamaño de la tabla
    void mostrarTodas() const;

    // Copia todas las estaciones a un arreglo dinamico (quien lo llama hace delete[])
    Estacion* copiarEnArreglo(int& cantidadCopiada) const;
};

#endif