#ifndef ESTACION_H
#define ESTACION_H

#include <string>

class Estacion {
private:
    std::string codigo;
    std::string nombre;
    std::string barrio;
    int capacidadAnclajes;
    int bicisDisponibles;

public:
    Estacion();
    Estacion(const std::string& codigo,
             const std::string& nombre,
             const std::string& barrio,
             int capacidadAnclajes,
             int bicisDisponibles);

    std::string getCodigo() const;
    std::string getNombre() const;
    std::string getBarrio() const;
    int getCapacidadAnclajes() const;
    int getBicisDisponibles() const;

    void setNombre(const std::string& nombre);
    void setBarrio(const std::string& barrio);
    void setCapacidadAnclajes(int capacidadAnclajes);
    void setBicisDisponibles(int bicisDisponibles);

    bool estaBajaOcupacion() const;

    void mostrar() const;
};

#endif