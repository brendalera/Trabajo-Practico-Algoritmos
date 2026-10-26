#include "Bicicleta.h"
#include <iostream>

Bicicleta::Bicicleta()
    : id(0),
      codigoEstacion(""),
      tipo(""),
      estado(""),
      kilometros(0.0) {
} //Constructor por defecto

Bicicleta::Bicicleta(int id,
                     const std::string& codigoEstacion,
                     const std::string& tipo,
                     const std::string& estado,
                     double kilometros)
    : id(id),
      codigoEstacion(codigoEstacion),
      tipo(tipo),
      estado(estado),
      kilometros(kilometros) {
} //Constructor con parametros

int Bicicleta::getId() const {
    return id;
}

std::string Bicicleta::getCodigoEstacion() const {
    return codigoEstacion;
}

std::string Bicicleta::getTipo() const {
    return tipo;
}

std::string Bicicleta::getEstado() const {
    return estado;
}

double Bicicleta::getKilometros() const {
    return kilometros;
}

void Bicicleta::setCodigoEstacion(const std::string& codigoEstacion) {
    this->codigoEstacion = codigoEstacion;
}

void Bicicleta::setTipo(const std::string& tipo) {
    this->tipo = tipo;
}

void Bicicleta::setEstado(const std::string& estado) {
    this->estado = estado;
}

void Bicicleta::setKilometros(double kilometros) {
    this->kilometros = kilometros;
}

bool Bicicleta::estaAveriada() const {
    return estado == "Averiada";
}

void Bicicleta::mostrar() const {
    std::cout << "ID: " << id << std::endl;
    std::cout << "Estacion: " << codigoEstacion << std::endl;
    std::cout << "Tipo: " << tipo << std::endl;
    std::cout << "Estado: " << estado << std::endl;
    std::cout << "Kilometros: " << kilometros << std::endl;
}