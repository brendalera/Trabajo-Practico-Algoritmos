#ifndef ORDENAMIENTO_ESTACIONES_H
#define ORDENAMIENTO_ESTACIONES_H

#include "Estacion.h"

// Ordenamiento por insercion, de menor a mayor.
// porCapacidad = true ordena por capacidad de anclajes,
// false ordena por bicicletas disponibles.

inline int claveDeOrden(const Estacion& estacion, bool porCapacidad) {
    return porCapacidad ? estacion.getCapacidadAnclajes()
                        : estacion.getBicisDisponibles();
}

inline void ordenarEstaciones(Estacion* arreglo, int cantidad, bool porCapacidad) {
    for (int i = 1; i < cantidad; i++) {
        Estacion actual = arreglo[i];
        int j = i - 1;

        while (j >= 0 &&
               claveDeOrden(arreglo[j], porCapacidad) >
               claveDeOrden(actual, porCapacidad)) {
            arreglo[j + 1] = arreglo[j];
            j--;
        }

        arreglo[j + 1] = actual;
    }
}

#endif