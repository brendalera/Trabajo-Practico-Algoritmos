#include "Estacion.h"
#include <iostream>

Estacion::Estacion()
    : codigo(""),
      nombre(""),
      barrio(""),
      capacidadAnclajes(0),
      bicisDisponibles(0) {
} //Constructor por defecto

Estacion::Estacion(const std::string& codigo,
                   const std::string& nombre,
                   const std::string& barrio,
                   int capacidadAnclajes,
                   int bicisDisponibles)
    : codigo(codigo),
      nombre(nombre),
      barrio(barrio),
      capacidadAnclajes(capacidadAnclajes),
      bicisDisponibles(bicisDisponibles) {
} //Constructor con parametros

std::string Estacion::getCodigo() const {
    return codigo;
}

std::string Estacion::getNombre() const {
    return nombre;
}

std::string Estacion::getBarrio() const {
    return barrio;
}

int Estacion::getCapacidadAnclajes() const {
    return capacidadAnclajes;
}

int Estacion::getBicisDisponibles() const {
    return bicisDisponibles;
}

void Estacion::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void Estacion::setBarrio(const std::string& barrio) {
    this->barrio = barrio;
}

void Estacion::setCapacidadAnclajes(int capacidadAnclajes) {
    this->capacidadAnclajes = capacidadAnclajes;
}

void Estacion::setBicisDisponibles(int bicisDisponibles) {
    this->bicisDisponibles = bicisDisponibles;
}

bool Estacion::estaBajaOcupacion() const {
    if (capacidadAnclajes == 0) {
        return false;
    }

    double ocupacion = static_cast<double>(bicisDisponibles) /
                       capacidadAnclajes;

    return ocupacion < 0.20; //declara si una estacion tiene menos del 20% de ocupacion
} 

void Estacion::mostrar() const {
    std::cout << "Codigo: " << codigo << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Barrio: " << barrio << std::endl;
    std::cout << "Capacidad de anclajes: " << capacidadAnclajes << std::endl;
    std::cout << "Bicicletas disponibles: " << bicisDisponibles << std::endl;
}