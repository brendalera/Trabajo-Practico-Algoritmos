#ifndef COLECCION_VIAJES_H
#define COLECCION_VIAJES_H

#include "Viaje.h"
#include <iostream>
#include <string>

// Arreglo dinamico de viajes que crece solo (sin vector).
class ColeccionViajes {
private:
    Viaje* viajes;
    int cantidad;
    int capacidad;

    void crecer() {
        int nuevaCapacidad = capacidad * 2;
        Viaje* nuevos = new Viaje[nuevaCapacidad];

        for (int i = 0; i < cantidad; i++) {
            nuevos[i] = viajes[i];
        }

        delete[] viajes;
        viajes = nuevos;
        capacidad = nuevaCapacidad;
    }

public:
    ColeccionViajes()
        : viajes(new Viaje[10]), cantidad(0), capacidad(10) {
    }

    ~ColeccionViajes() {
        delete[] viajes;
    }

    // evitamos copias superficiales de los punteros
    ColeccionViajes(const ColeccionViajes&) = delete;
    ColeccionViajes& operator=(const ColeccionViajes&) = delete;

    void agregar(const Viaje& viaje) {
        if (cantidad == capacidad) {
            crecer();
        }

        viajes[cantidad++] = viaje;
    }

    int getCantidad() const {
        return cantidad;
    }

    // B1: viajes que salieron de una estacion entre dos fechas (inclusive).
    // Las fechas AAAAMMDD se pueden comparar como texto.
    int contarViajesDesdeEstacion(const std::string& estacion,
                                  const std::string& fechaDesde,
                                  const std::string& fechaHasta) const {
        int total = 0;

        for (int i = 0; i < cantidad; i++) {
            if (viajes[i].getEstacionOrigen() == estacion &&
                viajes[i].getFecha() >= fechaDesde &&
                viajes[i].getFecha() <= fechaHasta) {
                total++;
            }
        }

        return total;
    }

    // B2: muestra los viajes de un usuario y devuelve el total de minutos
    int mostrarViajesDeUsuario(const std::string& dni, int& cantidadViajes) const {
        int minutos = 0;
        cantidadViajes = 0;

        for (int i = 0; i < cantidad; i++) {
            if (viajes[i].getDniUsuario() == dni) {
                viajes[i].mostrar();
                std::cout << "--------------------" << std::endl;
                minutos += viajes[i].getDuracionMin();
                cantidadViajes++;
            }
        }

        return minutos;
    }
};

#endif