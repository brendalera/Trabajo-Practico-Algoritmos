#include "Viaje.h"
#include <iostream>

Viaje::Viaje()
    : id(0),
      bicicletaId(0),
      dniUsuario(""),
      estacionOrigen(""),
      estacionDestino(""),
      fecha(""),
      duracionMin(0) {
} //Constructor por defecto

Viaje::Viaje(int id,
             int bicicletaId,
             const std::string& dniUsuario,
             const std::string& estacionOrigen,
             const std::string& estacionDestino,
             const std::string& fecha,
             int duracionMin)
    : id(id),
      bicicletaId(bicicletaId),
      dniUsuario(dniUsuario),
      estacionOrigen(estacionOrigen),
      estacionDestino(estacionDestino),
      fecha(fecha),
      duracionMin(duracionMin) {
} //Constructor con parametros

int Viaje::getId() const {
    return id;
}

int Viaje::getBicicletaId() const {
    return bicicletaId;
}

std::string Viaje::getDniUsuario() const {
    return dniUsuario;
}

std::string Viaje::getEstacionOrigen() const {
    return estacionOrigen;
}

std::string Viaje::getEstacionDestino() const {
    return estacionDestino;
}

std::string Viaje::getFecha() const {
    return fecha;
}

int Viaje::getDuracionMin() const {
    return duracionMin;
}

void Viaje::setEstacionOrigen(const std::string& estacionOrigen) {
    this->estacionOrigen = estacionOrigen;
}

void Viaje::setEstacionDestino(const std::string& estacionDestino) {
    this->estacionDestino = estacionDestino;
}

void Viaje::setDuracionMin(int duracionMin) {
    this->duracionMin = duracionMin;
}

void Viaje::mostrar() const {
    std::cout << "ID del viaje: " << id << std::endl;
    std::cout << "ID de la bicicleta: " << bicicletaId << std::endl;
    std::cout << "DNI del usuario: " << dniUsuario << std::endl;
    std::cout << "Estacion de origen: " << estacionOrigen << std::endl;
    std::cout << "Estacion de destino: " << estacionDestino << std::endl;
    std::cout << "Fecha: " << fecha << std::endl;
    std::cout << "Duracion: " << duracionMin << " minutos" << std::endl;
}