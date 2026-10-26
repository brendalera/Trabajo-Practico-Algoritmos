#include <iostream>
#include <fstream>
#include <string>
#include "Estacion.h"
#include "OrdenamientoEstaciones.h"
#include "TablaHash.h"
#include "Grafo.h"
#include "Bicicleta.h"
#include "ArbolBicicletas.h"
#include "Viaje.h"
#include "ColeccionViajes.h"
#include "GestorEspera.h"
#include "MinHeap.h"
#include "Redistribucion.h"

// Carga de archivos

bool cargarEstaciones(const std::string& ruta, TablaHash& tabla, Grafo& grafo) {
    std::ifstream archivo(ruta);

    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir " << ruta << std::endl;
        return false;
    }

    std::string codigo, nombre, barrio;
    int capacidad, bicis;

    while (archivo >> codigo >> nombre >> barrio >> capacidad >> bicis) {
        if (tabla.insertar(Estacion(codigo, nombre, barrio, capacidad, bicis))) {
            grafo.agregarEstacion(codigo);
        }
    }

    return true;
}

bool cargarCiclovias(const std::string& ruta, Grafo& grafo) {
    std::ifstream archivo(ruta);

    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir " << ruta << std::endl;
        return false;
    }

    std::string a, b;

    while (archivo >> a >> b) {
        grafo.agregarCiclovia(a, b);
    }

    return true;
}

bool cargarBicicletas(const std::string& ruta, ArbolBicicletas& arbol) {
    std::ifstream archivo(ruta);

    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir " << ruta << std::endl;
        return false;
    }

    int id;
    std::string codigo, tipo, estado;
    double km;

    while (archivo >> id >> codigo >> tipo >> estado >> km) {
        arbol.insertar(Bicicleta(id, codigo, tipo, estado, km));
    }

    return true;
}

bool cargarViajes(const std::string& ruta, ColeccionViajes& viajes) {
    std::ifstream archivo(ruta);

    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir " << ruta << std::endl;
        return false;
    }

    int id, bicicletaId, duracion;
    std::string dni, origen, destino, fecha;

    while (archivo >> id >> bicicletaId >> dni >> origen >> destino >> fecha >> duracion) {
        viajes.agregar(Viaje(id, bicicletaId, dni, origen, destino, fecha, duracion));
    }

    return true;
}

// ---------- Menu ----------

void mostrarMenu() {
    std::cout << "\n===== SISTEMA DE BICICLETAS PUBLICAS =====" << std::endl;
    std::cout << "--- Estaciones ---" << std::endl;
    std::cout << " 1. Mostrar estacion por codigo" << std::endl;
    std::cout << " 2. Agregar estacion" << std::endl;
    std::cout << " 3. Eliminar estacion" << std::endl;
    std::cout << " 4. Recorrido mas corto entre dos estaciones (BFS)" << std::endl;
    std::cout << " 5. Info de la tabla hash (colisiones y factor de carga)" << std::endl;
    std::cout << "11. Listar estaciones ordenadas (capacidad o bicis disponibles)" << std::endl;
    std::cout << "12. Listar estaciones con menos del 20% de ocupacion" << std::endl;
    std::cout << "--- Bicicletas (arbol) ---" << std::endl;
    std::cout << " 6. Buscar bicicleta por ID" << std::endl;
    std::cout << " 7. Listar bicicletas ordenadas por ID" << std::endl;
    std::cout << " 8. Contar bicicletas averiadas" << std::endl;
    std::cout << " 9. Altura del arbol" << std::endl;
    std::cout << "10. Bicicletas con mas de X km" << std::endl;
    std::cout << "--- Viajes ---" << std::endl;
    std::cout << "13. Viajes desde una estacion en un rango de fechas" << std::endl;
    std::cout << "14. Viajes de un usuario por DNI (con total de minutos)" << std::endl;
    std::cout << "--- Colas de espera ---" << std::endl;
    std::cout << "15. Retirar una bici (si no hay, el usuario se encola)" << std::endl;
    std::cout << "16. Devolver una bici" << std::endl;
    std::cout << "17. Ver la cola de espera de una estacion" << std::endl;
    std::cout << "--- Taller de reparaciones (heap) ---" << std::endl;
    std::cout << "18. Enviar una bici averiada al taller" << std::endl;
    std::cout << "19. Atender la bici mas urgente del taller" << std::endl;
    std::cout << "--- Redistribucion (backtracking) ---" << std::endl;
    std::cout << "20. Calcular a que estaciones lleva bicis el camion" << std::endl;
    std::cout << " 0. Salir" << std::endl;
    std::cout << "Opcion: ";
}

int main() {
    TablaHash tabla;
    Grafo grafo;
    ArbolBicicletas arbol;
    ColeccionViajes viajes;
    GestorEspera espera;
    MinHeap taller;

    cargarEstaciones("archivos/estaciones.txt", tabla, grafo);
    cargarCiclovias("archivos/ciclovias.txt", grafo);
    cargarBicicletas("archivos/bicicletas.txt", arbol);
    cargarViajes("archivos/viajes.txt", viajes);

    std::cout << "Estaciones cargadas: " << tabla.getCantidad() << std::endl;
    std::cout << "Bicicletas cargadas: " << arbol.getCantidad() << std::endl;
    std::cout << "Viajes cargados: " << viajes.getCantidad() << std::endl;

    int opcion = -1;

    while (opcion != 0) {
        mostrarMenu();

        if (!(std::cin >> opcion)) {
            break; // entrada invalida o fin de datos
        }

        if (opcion == 1) {
            std::string codigo;
            std::cout << "Codigo: ";
            std::cin >> codigo;

            Estacion estacion;
            if (tabla.buscar(codigo, estacion)) {
                estacion.mostrar();
            } else {
                std::cout << "No existe esa estacion." << std::endl;
            }
        } else if (opcion == 2) {
            std::string codigo, nombre, barrio;
            int capacidad, bicis;

            std::cout << "Codigo nombre barrio capacidad bicisDisponibles: ";
            std::cin >> codigo >> nombre >> barrio >> capacidad >> bicis;

            if (tabla.insertar(Estacion(codigo, nombre, barrio, capacidad, bicis))) {
                grafo.agregarEstacion(codigo);
                std::cout << "Estacion agregada." << std::endl;
            } else {
                std::cout << "Ya existe una estacion con ese codigo." << std::endl;
            }
        } else if (opcion == 3) {
            std::string codigo;
            std::cout << "Codigo: ";
            std::cin >> codigo;

            if (tabla.eliminar(codigo)) {
                grafo.eliminarEstacion(codigo);
                std::cout << "Estacion eliminada." << std::endl;
            } else {
                std::cout << "No existe esa estacion." << std::endl;
            }
        } else if (opcion == 4) {
            std::string origen, destino;
            std::cout << "Origen y destino: ";
            std::cin >> origen >> destino;

            grafo.caminoMasCorto(origen, destino);
        } else if (opcion == 5) {
            std::cout << "Colisiones: " << tabla.getColisiones() << std::endl;
            std::cout << "Factor de carga: " << tabla.factorCarga() << std::endl;
        } else if (opcion == 6) {
            int id;
            std::cout << "ID: ";
            std::cin >> id;

            const Bicicleta* bici = arbol.buscar(id);
            if (bici != nullptr) {
                bici->mostrar();
            } else {
                std::cout << "No existe esa bicicleta." << std::endl;
            }
        } else if (opcion == 7) {
            arbol.listarInorder();
        } else if (opcion == 8) {
            std::cout << "Averiadas: " << arbol.contarAveriadas() << std::endl;
        } else if (opcion == 9) {
            std::cout << "Altura: " << arbol.altura() << std::endl;
        } else if (opcion == 10) {
            double km;
            std::cout << "Kilometros: ";
            std::cin >> km;

            int encontradas = arbol.listarMasDeKm(km);
            std::cout << "Encontradas: " << encontradas << std::endl;
        } else if (opcion == 11) {
            int criterio;
            std::cout << "Ordenar por: 1) capacidad de anclajes  2) bicis disponibles: ";
            std::cin >> criterio;

            int cantidad = 0;
            Estacion* estaciones = tabla.copiarEnArreglo(cantidad);

            ordenarEstaciones(estaciones, cantidad, criterio == 1);

            for (int i = 0; i < cantidad; i++) {
                estaciones[i].mostrar();
                std::cout << "--------------------" << std::endl;
            }

            delete[] estaciones;
        } else if (opcion == 12) {
            int cantidad = 0;
            Estacion* estaciones = tabla.copiarEnArreglo(cantidad);
            int encontradas = 0;

            for (int i = 0; i < cantidad; i++) {
                if (estaciones[i].estaBajaOcupacion()) {
                    estaciones[i].mostrar();
                    std::cout << "--------------------" << std::endl;
                    encontradas++;
                }
            }

            if (encontradas == 0) {
                std::cout << "No hay estaciones con menos del 20%." << std::endl;
            }

            delete[] estaciones;
        } else if (opcion == 13) {
            std::string estacion, desde, hasta;
            std::cout << "Estacion, fecha desde y fecha hasta (AAAAMMDD): ";
            std::cin >> estacion >> desde >> hasta;

            std::cout << "Viajes: "
                      << viajes.contarViajesDesdeEstacion(estacion, desde, hasta)
                      << std::endl;
        } else if (opcion == 14) {
            std::string dni;
            std::cout << "DNI: ";
            std::cin >> dni;

            int cantidadViajes = 0;
            int minutos = viajes.mostrarViajesDeUsuario(dni, cantidadViajes);

            if (cantidadViajes == 0) {
                std::cout << "Ese usuario no tiene viajes." << std::endl;
            } else {
                std::cout << "Viajes: " << cantidadViajes
                          << " - Total de minutos: " << minutos << std::endl;
            }
        } else if (opcion == 15) {
            std::string codigo, dni;
            std::cout << "Estacion y DNI del usuario: ";
            std::cin >> codigo >> dni;

            Estacion* estacion = tabla.obtener(codigo);

            if (estacion == nullptr) {
                std::cout << "No existe esa estacion." << std::endl;
            } else if (estacion->getBicisDisponibles() > 0) {
                estacion->setBicisDisponibles(estacion->getBicisDisponibles() - 1);
                std::cout << "El usuario " << dni << " retiro una bici. Quedan "
                          << estacion->getBicisDisponibles() << "." << std::endl;
            } else {
                int posicion = espera.obtenerCola(codigo).encolar(dni);
                std::cout << "No hay bicis. El usuario " << dni
                          << " quedo en la cola, posicion " << posicion << "." << std::endl;
            }
        } else if (opcion == 16) {
            std::string codigo;
            std::cout << "Estacion donde se devuelve la bici: ";
            std::cin >> codigo;

            Estacion* estacion = tabla.obtener(codigo);
            std::string dniAsignado;

            if (estacion == nullptr) {
                std::cout << "No existe esa estacion." << std::endl;
            } else if (espera.obtenerCola(codigo).desencolar(dniAsignado)) {
                std::cout << "Bici devuelta y asignada al usuario " << dniAsignado
                          << " (primero de la cola)." << std::endl;
            } else if (estacion->getBicisDisponibles() >= estacion->getCapacidadAnclajes()) {
                std::cout << "La estacion no tiene anclajes libres." << std::endl;
            } else {
                estacion->setBicisDisponibles(estacion->getBicisDisponibles() + 1);
                std::cout << "Bici devuelta. Ahora hay "
                          << estacion->getBicisDisponibles() << "." << std::endl;
            }
        } else if (opcion == 17) {
            std::string codigo;
            std::cout << "Estacion: ";
            std::cin >> codigo;

            ColaEspera& cola = espera.obtenerCola(codigo);

            if (cola.estaVacia()) {
                std::cout << "La cola esta vacia." << std::endl;
            } else {
                std::cout << "Usuarios esperando: " << cola.getCantidad() << std::endl;
                cola.mostrar();
            }
        } else if (opcion == 18) {
            int id;
            std::cout << "ID de la bicicleta: ";
            std::cin >> id;

            const Bicicleta* bici = arbol.buscar(id);

            if (bici == nullptr) {
                std::cout << "No existe esa bicicleta." << std::endl;
            } else if (!bici->estaAveriada()) {
                std::cout << "La bicicleta no esta averiada." << std::endl;
            } else if (taller.contiene(id)) {
                std::cout << "La bicicleta ya esta en el taller." << std::endl;
            } else {
                int prioridad = 1; // las electricas entran siempre con 1

                if (bici->getTipo() != "Electrica") {
                    std::cout << "Prioridad (1 = mas urgente, 3 = menos urgente): ";
                    std::cin >> prioridad;
                }

                if (taller.insertar(*bici, prioridad)) {
                    std::cout << "Bicicleta " << id << " enviada al taller con prioridad "
                              << prioridad << "." << std::endl;
                } else {
                    std::cout << "Prioridad invalida (tiene que ser 1, 2 o 3)." << std::endl;
                }
            }
        } else if (opcion == 19) {
            Bicicleta atendida;
            int prioridad = 0;

            if (taller.extraerMasUrgente(atendida, prioridad)) {
                std::cout << "Se atiende la bicicleta " << atendida.getId()
                          << " (" << atendida.getTipo() << ", prioridad "
                          << prioridad << ")." << std::endl;
            } else {
                std::cout << "El taller no tiene bicicletas." << std::endl;
            }
        } else if (opcion == 20) {
            int capacidadCamion, cantidadEstaciones;
            std::cout << "Capacidad del camion: ";
            std::cin >> capacidadCamion;
            std::cout << "Cantidad de estaciones con faltantes: ";
            std::cin >> cantidadEstaciones;

            Redistribucion redistribucion;

            for (int i = 0; i < cantidadEstaciones; i++) {
                std::string codigo;
                int faltante;
                std::cout << "Estacion " << (i + 1) << " (codigo faltante): ";
                std::cin >> codigo >> faltante;

                if (!redistribucion.agregarEstacion(codigo, faltante)) {
                    std::cout << "El faltante tiene que ser mayor a 0. Se ignora." << std::endl;
                }
            }

            if (capacidadCamion <= 0) {
                std::cout << "La capacidad tiene que ser mayor a 0." << std::endl;
            } else {
                int cantidadSoluciones = redistribucion.resolver(capacidadCamion);
                std::cout << "Soluciones encontradas: " << cantidadSoluciones << std::endl;
            }
        } else if (opcion != 0) {
            std::cout << "Opcion invalida." << std::endl;
        }
    }

    return 0;
}