#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include "Bicicleta.h"

// Cola de prioridad del taller: min-heap guardado en un arreglo dinamico.
// Prioridad 1 = mas urgente, 3 = menos urgente.
// Si dos bicis tienen la misma prioridad, sale primero la que entro antes.
class MinHeap {
private:
    struct Item {
        Bicicleta bicicleta;
        int prioridad;
        int orden; // orden de llegada, desempata prioridades iguales
    };

    Item* items;
    int cantidad;
    int capacidad;
    int proximoOrden;

    // true si a debe salir antes que b
    bool esMasUrgente(const Item& a, const Item& b) const {
        if (a.prioridad != b.prioridad) {
            return a.prioridad < b.prioridad;
        }

        return a.orden < b.orden;
    }

    void intercambiar(int i, int j) {
        Item temporal = items[i];
        items[i] = items[j];
        items[j] = temporal;
    }

    void crecer() {
        int nuevaCapacidad = capacidad * 2;
        Item* nuevos = new Item[nuevaCapacidad];

        for (int i = 0; i < cantidad; i++) {
            nuevos[i] = items[i];
        }

        delete[] items;
        items = nuevos;
        capacidad = nuevaCapacidad;
    }

    // Sube el elemento mientras sea mas urgente que su padre
    void subir(int posicion) {
        while (posicion > 0) {
            int padre = (posicion - 1) / 2;

            if (!esMasUrgente(items[posicion], items[padre])) {
                break;
            }

            intercambiar(posicion, padre);
            posicion = padre;
        }
    }

    // Baja el elemento mientras algun hijo sea mas urgente
    void bajar(int posicion) {
        while (true) {
            int izquierdo = 2 * posicion + 1;
            int derecho = 2 * posicion + 2;
            int masUrgente = posicion;

            if (izquierdo < cantidad && esMasUrgente(items[izquierdo], items[masUrgente])) {
                masUrgente = izquierdo;
            }

            if (derecho < cantidad && esMasUrgente(items[derecho], items[masUrgente])) {
                masUrgente = derecho;
            }

            if (masUrgente == posicion) {
                break;
            }

            intercambiar(posicion, masUrgente);
            posicion = masUrgente;
        }
    }

public:
    MinHeap()
        : items(new Item[10]), cantidad(0), capacidad(10), proximoOrden(0) {
    }

    ~MinHeap() {
        delete[] items;
    }

    // evitamos copias superficiales de los punteros
    MinHeap(const MinHeap&) = delete;
    MinHeap& operator=(const MinHeap&) = delete;

    // Operacion 1: insertar. Devuelve false si la prioridad no es 1, 2 o 3.
    bool insertar(const Bicicleta& bicicleta, int prioridad) {
        if (prioridad < 1 || prioridad > 3) {
            return false;
        }

        if (cantidad == capacidad) {
            crecer();
        }

        items[cantidad].bicicleta = bicicleta;
        items[cantidad].prioridad = prioridad;
        items[cantidad].orden = proximoOrden++;
        subir(cantidad);
        cantidad++;

        return true;
    }

    // Operacion 2: extraer la mas urgente. Devuelve false si esta vacio.
    bool extraerMasUrgente(Bicicleta& bicicleta, int& prioridad) {
        if (cantidad == 0) {
            return false;
        }

        bicicleta = items[0].bicicleta;
        prioridad = items[0].prioridad;

        cantidad--;
        items[0] = items[cantidad];
        bajar(0);

        return true;
    }

    // Auxiliar para no cargar dos veces la misma bici (recorre todo: O(n))
    bool contiene(int id) const {
        for (int i = 0; i < cantidad; i++) {
            if (items[i].bicicleta.getId() == id) {
                return true;
            }
        }

        return false;
    }

    bool estaVacio() const {
        return cantidad == 0;
    }

    int getCantidad() const {
        return cantidad;
    }
};

#endif