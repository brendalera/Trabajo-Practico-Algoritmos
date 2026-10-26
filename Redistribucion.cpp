#include "Redistribucion.h"
#include <iostream>

Redistribucion::Redistribucion()
    : codigos(new std::string[10]),
      faltantes(new int[10]),
      elegidas(nullptr),
      cantidad(0),
      capacidad(10),
      capacidadCamion(0),
      soluciones(0) {
}

Redistribucion::~Redistribucion() {
    delete[] codigos;
    delete[] faltantes;
    delete[] elegidas;
}

void Redistribucion::crecer() {
    int nuevaCapacidad = capacidad * 2;
    std::string* nuevosCodigos = new std::string[nuevaCapacidad];
    int* nuevosFaltantes = new int[nuevaCapacidad];

    for (int i = 0; i < cantidad; i++) {
        nuevosCodigos[i] = codigos[i];
        nuevosFaltantes[i] = faltantes[i];
    }

    delete[] codigos;
    delete[] faltantes;
    codigos = nuevosCodigos;
    faltantes = nuevosFaltantes;
    capacidad = nuevaCapacidad;
}

bool Redistribucion::agregarEstacion(const std::string& codigo, int faltante) {
    if (faltante <= 0) {
        return false;
    }

    if (cantidad == capacidad) {
        crecer();
    }

    codigos[cantidad] = codigo;
    faltantes[cantidad] = faltante;
    cantidad++;

    return true;
}

void Redistribucion::mostrarSolucion() const {
    std::cout << "{";
    bool primera = true;

    for (int i = 0; i < cantidad; i++) {
        if (elegidas[i]) {
            if (!primera) {
                std::cout << ", ";
            }

            std::cout << codigos[i];
            primera = false;
        }
    }

    std::cout << "}" << std::endl;
}

// Para cada estacion hay dos caminos: llevarle bicis o no.
// Si la suma se pasa de la capacidad, se descarta esa rama (poda).
void Redistribucion::buscar(int indice, int sumaActual) {
    if (sumaActual == capacidadCamion) {
        mostrarSolucion();
        soluciones++;
        return;
    }

    if (indice == cantidad) {
        return;
    }

    // Opcion 1: incluir la estacion (solo si no se pasa)
    if (sumaActual + faltantes[indice] <= capacidadCamion) {
        elegidas[indice] = true;
        buscar(indice + 1, sumaActual + faltantes[indice]);
        elegidas[indice] = false; // backtrack: deshacer la eleccion
    }

    // Opcion 2: no incluirla
    buscar(indice + 1, sumaActual);
}

int Redistribucion::resolver(int capacidadDelCamion) {
    capacidadCamion = capacidadDelCamion;
    soluciones = 0;

    delete[] elegidas;
    elegidas = new bool[cantidad > 0 ? cantidad : 1];

    for (int i = 0; i < cantidad; i++) {
        elegidas[i] = false;
    }

    buscar(0, 0);

    if (soluciones == 0) {
        std::cout << "No hay ninguna combinacion de estaciones que sume exactamente "
                  << capacidadCamion << "." << std::endl;
    }

    return soluciones;
}

int Redistribucion::getCantidad() const {
    return cantidad;
}