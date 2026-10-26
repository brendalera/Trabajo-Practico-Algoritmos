#ifndef BICICLETA_H
#define BICICLETA_H

#include <string>

class Bicicleta {
private:
    int id;
    std::string codigoEstacion;
    std::string tipo;
    std::string estado;
    double kilometros;

public:
    Bicicleta();

    Bicicleta(int id,
              const std::string& codigoEstacion,
              const std::string& tipo,
              const std::string& estado,
              double kilometros);

    int getId() const;
    std::string getCodigoEstacion() const;
    std::string getTipo() const;
    std::string getEstado() const;
    double getKilometros() const;

    void setCodigoEstacion(const std::string& codigoEstacion);
    void setTipo(const std::string& tipo);
    void setEstado(const std::string& estado);
    void setKilometros(double kilometros);

    bool estaAveriada() const;
    void mostrar() const;
};

#endif
