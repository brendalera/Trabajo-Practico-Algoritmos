#ifndef GESTOR_ESPERA_H
#define GESTOR_ESPERA_H

#include "ColaEspera.h"
#include <string>

// Mantiene una ColaEspera por estacion (se crea la primera vez que se usa).
class GestorEspera {
private:
    std::string* codigos;
    ColaEspera** colas;
    int cantidad;
    int capacidad;

    int indiceDe(const std::string& codigo) const {
        for (int i = 0; i < cantidad; i++) {
            if (codigos[i] == codigo) {
                return i;
            }
        }

        return -1;
    }

    void crecer() {
        int nuevaCapacidad = capacidad * 2;
        std::string* nuevosCodigos = new std::string[nuevaCapacidad];
        ColaEspera** nuevasColas = new ColaEspera*[nuevaCapacidad];

        for (int i = 0; i < cantidad; i++) {
            nuevosCodigos[i] = codigos[i];
            nuevasColas[i] = colas[i];
        }

        delete[] codigos;
        delete[] colas;
        codigos = nuevosCodigos;
        colas = nuevasColas;
        capacidad = nuevaCapacidad;
    }

public:
    GestorEspera()
        : codigos(new std::string[10]),
          colas(new ColaEspera*[10]),
          cantidad(0),
          capacidad(10) {
    }

    ~GestorEspera() {
        for (int i = 0; i < cantidad; i++) {
            delete colas[i];
        }

        delete[] codigos;
        delete[] colas;
    }

    // evitamos copias superficiales de los punteros
    GestorEspera(const GestorEspera&) = delete;
    GestorEspera& operator=(const GestorEspera&) = delete;

    // Devuelve la cola de la estacion, creandola si todavia no existe
    ColaEspera& obtenerCola(const std::string& codigo) {
        int indice = indiceDe(codigo);

        if (indice == -1) {
            if (cantidad == capacidad) {
                crecer();
            }

            codigos[cantidad] = codigo;
            colas[cantidad] = new ColaEspera();
            indice = cantidad++;
        }

        return *colas[indice];
    }
};

#endif