#ifndef REDISTRIBUCION_H
#define REDISTRIBUCION_H

#include <string>

// Busca, con backtracking, todos los subconjuntos de estaciones cuyos
// faltantes suman exactamente la capacidad del camion.
class Redistribucion {
private:
    std::string* codigos;
    int* faltantes;
    bool* elegidas;       // estaciones elegidas en la combinacion actual
    int cantidad;
    int capacidad;        // tamanio de los arreglos
    int capacidadCamion;
    int soluciones;

    void crecer();
    void buscar(int indice, int sumaActual);
    void mostrarSolucion() const;

public:
    Redistribucion();
    ~Redistribucion();

    // evitamos copias superficiales de los punteros
    Redistribucion(const Redistribucion&) = delete;
    Redistribucion& operator=(const Redistribucion&) = delete;

    // Devuelve false si el faltante no es positivo
    bool agregarEstacion(const std::string& codigo, int faltante);

    // Muestra todas las soluciones y devuelve cuantas hay
    int resolver(int capacidadCamion);

    int getCantidad() const;
};

#endif