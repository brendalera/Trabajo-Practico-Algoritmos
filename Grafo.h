#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <string>

// Grafo no dirigido: nodos = estaciones, aristas = ciclovias.

class Grafo {
private:
    struct Arista {
        int destino;
        Arista* siguiente;

        Arista(int destino, Arista* siguiente)
            : destino(destino), siguiente(siguiente) {
        }
    };

    std::string* codigos;   // codigos[i] = codigo de la estacion i
    bool* activas;          // false si la estacion fue eliminada
    Arista** adyacencia;    // adyacencia[i] = lista de vecinos de i
    int cantidad;           // nodos usados (incluye eliminados)
    int capacidad;          // tamaño de los arreglos

    int indiceDe(const std::string& codigo) const {
        for (int i = 0; i < cantidad; i++) {
            if (activas[i] && codigos[i] == codigo) {
                return i;
            }
        }

        return -1;
    }

    // Duplica la capacidad de los arreglos
    void crecer() {
        int nuevaCapacidad = capacidad * 2;

        std::string* nuevosCodigos = new std::string[nuevaCapacidad];
        bool* nuevasActivas = new bool[nuevaCapacidad];
        Arista** nuevaAdyacencia = new Arista*[nuevaCapacidad];

        for (int i = 0; i < nuevaCapacidad; i++) {
            if (i < cantidad) {
                nuevosCodigos[i] = codigos[i];
                nuevasActivas[i] = activas[i];
                nuevaAdyacencia[i] = adyacencia[i];
            } else {
                nuevasActivas[i] = false;
                nuevaAdyacencia[i] = nullptr;
            }
        }

        delete[] codigos;
        delete[] activas;
        delete[] adyacencia;

        codigos = nuevosCodigos;
        activas = nuevasActivas;
        adyacencia = nuevaAdyacencia;
        capacidad = nuevaCapacidad;
    }

    bool existeArista(int a, int b) const {
        Arista* actual = adyacencia[a];

        while (actual != nullptr) {
            if (actual->destino == b) {
                return true;
            }

            actual = actual->siguiente;
        }

        return false;
    }

    void liberarAristas(int nodo) {
        Arista* actual = adyacencia[nodo];

        while (actual != nullptr) {
            Arista* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }

        adyacencia[nodo] = nullptr;
    }

    // Saca de la lista de "nodo" la arista que apunta a "destino"
    void quitarArista(int nodo, int destino) {
        Arista* actual = adyacencia[nodo];
        Arista* anterior = nullptr;

        while (actual != nullptr) {
            if (actual->destino == destino) {
                if (anterior == nullptr) {
                    adyacencia[nodo] = actual->siguiente;
                } else {
                    anterior->siguiente = actual->siguiente;
                }

                delete actual;
                return;
            }

            anterior = actual;
            actual = actual->siguiente;
        }
    }

public:
    Grafo()
        : codigos(new std::string[10]),
          activas(new bool[10]),
          adyacencia(new Arista*[10]),
          cantidad(0),
          capacidad(10) {
        for (int i = 0; i < capacidad; i++) {
            activas[i] = false;
            adyacencia[i] = nullptr;
        }
    }

    ~Grafo() {
        for (int i = 0; i < cantidad; i++) {
            liberarAristas(i);
        }

        delete[] codigos;
        delete[] activas;
        delete[] adyacencia;
    }

    // evitamos copias superficiales de los punteros
    Grafo(const Grafo&) = delete;
    Grafo& operator=(const Grafo&) = delete;

    bool existeEstacion(const std::string& codigo) const {
        return indiceDe(codigo) != -1;
    }

    bool agregarEstacion(const std::string& codigo) {
        if (existeEstacion(codigo)) {
            return false;
        }

        if (cantidad == capacidad) {
            crecer();
        }

        codigos[cantidad] = codigo;
        activas[cantidad] = true;
        adyacencia[cantidad] = nullptr;
        cantidad++;

        return true;
    }

    // Ciclovia bidireccional. Devuelve false si falta alguna estacion
    // o si la ciclovia ya estaba cargada.
    bool agregarCiclovia(const std::string& a, const std::string& b) {
        int indiceA = indiceDe(a);
        int indiceB = indiceDe(b);

        if (indiceA == -1 || indiceB == -1 || indiceA == indiceB) {
            return false;
        }

        if (existeArista(indiceA, indiceB)) {
            return false;
        }

        adyacencia[indiceA] = new Arista(indiceB, adyacencia[indiceA]);
        adyacencia[indiceB] = new Arista(indiceA, adyacencia[indiceB]);

        return true;
    }

    // Elimina la estacion y todas las ciclovias que llegan a ella
    bool eliminarEstacion(const std::string& codigo) {
        int indice = indiceDe(codigo);

        if (indice == -1) {
            return false;
        }

        for (int i = 0; i < cantidad; i++) {
            if (i != indice && activas[i]) {
                quitarArista(i, indice);
            }
        }

        liberarAristas(indice);
        activas[indice] = false;

        return true;
    }

    // BFS: imprime el recorrido con menos tramos entre dos estaciones.
    // Devuelve la cantidad de tramos, o -1 si no hay recorrido.
    int caminoMasCorto(const std::string& origen,
                       const std::string& destino) const {
        int indiceOrigen = indiceDe(origen);
        int indiceDestino = indiceDe(destino);

        if (indiceOrigen == -1 || indiceDestino == -1) {
            std::cout << "Alguna de las estaciones no existe." << std::endl;
            return -1;
        }

        bool* visitado = new bool[cantidad];
        int* padre = new int[cantidad];
        int* cola = new int[cantidad]; // cada nodo entra una sola vez
        int frente = 0;
        int fin = 0;

        for (int i = 0; i < cantidad; i++) {
            visitado[i] = false;
            padre[i] = -1;
        }

        cola[fin++] = indiceOrigen;
        visitado[indiceOrigen] = true;

        while (frente < fin && !visitado[indiceDestino]) {
            int actual = cola[frente++];
            Arista* vecino = adyacencia[actual];

            while (vecino != nullptr) {
                if (!visitado[vecino->destino]) {
                    visitado[vecino->destino] = true;
                    padre[vecino->destino] = actual;
                    cola[fin++] = vecino->destino;
                }

                vecino = vecino->siguiente;
            }
        }

        int tramos = -1;

        if (!visitado[indiceDestino]) {
            std::cout << "No existe recorrido por ciclovias entre "
                      << origen << " y " << destino << "." << std::endl;
        } else {
            // Reconstruimos el camino yendo del destino al origen
            int* ruta = new int[cantidad];
            int largo = 0;

            for (int nodo = indiceDestino; nodo != -1; nodo = padre[nodo]) {
                ruta[largo++] = nodo;
            }

            tramos = largo - 1;

            std::cout << "Recorrido (" << tramos << " tramos): ";

            for (int i = largo - 1; i >= 0; i--) {
                std::cout << codigos[ruta[i]];

                if (i > 0) {
                    std::cout << " -> ";
                }
            }

            std::cout << std::endl;

            delete[] ruta;
        }

        delete[] visitado;
        delete[] padre;
        delete[] cola;

        return tramos;
    }
};

#endif