#ifndef VIAJE_H
#define VIAJE_H

#include <string>

class Viaje {
private:
    int id;
    int bicicletaId;
    std::string dniUsuario;
    std::string estacionOrigen;
    std::string estacionDestino;
    std::string fecha;
    int duracionMin;

public:
    Viaje();

    Viaje(int id,
          int bicicletaId,
          const std::string& dniUsuario,
          const std::string& estacionOrigen,
          const std::string& estacionDestino,
          const std::string& fecha,
          int duracionMin);

    int getId() const;
    int getBicicletaId() const;
    std::string getDniUsuario() const;
    std::string getEstacionOrigen() const;
    std::string getEstacionDestino() const;
    std::string getFecha() const;
    int getDuracionMin() const;

    void setEstacionOrigen(const std::string& estacionOrigen);
    void setEstacionDestino(const std::string& estacionDestino);
    void setDuracionMin(int duracionMin);

    void mostrar() const;
};

#endif