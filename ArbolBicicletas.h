#ifndef ARBOL_BICICLETAS_H
#define ARBOL_BICICLETAS_H

#include "Bicicleta.h"
#include <iostream>

class ArbolBicicletas {
private:
    struct Nodo {
        Bicicleta bicicleta;
        Nodo* izquierdo;
        Nodo* derecho;

        Nodo(const Bicicleta& bicicleta)
            : bicicleta(bicicleta), izquierdo(nullptr), derecho(nullptr) {
        }
    };

    Nodo* raiz;
    int cantidad;

    // Inserta de forma recursiva. Si el id ya existe, no inserta.
    Nodo* insertar(Nodo* nodo, const Bicicleta& bicicleta, bool& insertada) {
        if (nodo == nullptr) {
            insertada = true;
            return new Nodo(bicicleta);
        }

        if (bicicleta.getId() < nodo->bicicleta.getId()) {
            nodo->izquierdo = insertar(nodo->izquierdo, bicicleta, insertada);
        } else if (bicicleta.getId() > nodo->bicicleta.getId()) {
            nodo->derecho = insertar(nodo->derecho, bicicleta, insertada);
        }

        return nodo;
    }

    // Recorrido inorder: izquierdo, raiz, derecho (queda ordenado por id)
    void inorder(const Nodo* nodo) const {
        if (nodo == nullptr) {
            return;
        }

        inorder(nodo->izquierdo);
        nodo->bicicleta.mostrar();
        std::cout << "--------------------" << std::endl;
        inorder(nodo->derecho);
    }

    int contarAveriadas(const Nodo* nodo) const {
        if (nodo == nullptr) {
            return 0;
        }

        int total = contarAveriadas(nodo->izquierdo) +
                    contarAveriadas(nodo->derecho);

        if (nodo->bicicleta.estaAveriada()) {
            total++;
        }

        return total;
    }

    // Altura: arbol vacio = 0, un solo nodo = 1
    int altura(const Nodo* nodo) const {
        if (nodo == nullptr) {
            return 0;
        }

        int alturaIzquierda = altura(nodo->izquierdo);
        int alturaDerecha = altura(nodo->derecho);

        return 1 + (alturaIzquierda > alturaDerecha ? alturaIzquierda
                                                     : alturaDerecha);
    }

    // B3: lista bicis con mas de X km (recorre inorder)
    int listarMasDeKm(const Nodo* nodo, double km) const {
        if (nodo == nullptr) {
            return 0;
        }

        int encontradas = listarMasDeKm(nodo->izquierdo, km);

        if (nodo->bicicleta.getKilometros() > km) {
            nodo->bicicleta.mostrar();
            std::cout << "--------------------" << std::endl;
            encontradas++;
        }

        encontradas += listarMasDeKm(nodo->derecho, km);

        return encontradas;
    }

    // Postorder: hijos primero, despues el nodo
    void liberar(Nodo* nodo) {
        if (nodo == nullptr) {
            return;
        }

        liberar(nodo->izquierdo);
        liberar(nodo->derecho);
        delete nodo;
    }

    // Opcional: eliminar contemplando los 3 casos
    Nodo* eliminar(Nodo* nodo, int id, bool& eliminada) {
        if (nodo == nullptr) {
            return nullptr;
        }

        if (id < nodo->bicicleta.getId()) {
            nodo->izquierdo = eliminar(nodo->izquierdo, id, eliminada);
        } else if (id > nodo->bicicleta.getId()) {
            nodo->derecho = eliminar(nodo->derecho, id, eliminada);
        } else {
            eliminada = true;

            // Caso 1: hoja
            if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) {
                delete nodo;
                return nullptr;
            }

            // Caso 2: un solo hijo
            if (nodo->izquierdo == nullptr) {
                Nodo* hijo = nodo->derecho;
                delete nodo;
                return hijo;
            }

            if (nodo->derecho == nullptr) {
                Nodo* hijo = nodo->izquierdo;
                delete nodo;
                return hijo;
            }

            // Caso 3: dos hijos -> reemplazar por el sucesor inorder
            // (el menor del subarbol derecho)
            Nodo* sucesor = nodo->derecho;
            while (sucesor->izquierdo != nullptr) {
                sucesor = sucesor->izquierdo;
            }

            nodo->bicicleta = sucesor->bicicleta;
            nodo->derecho = eliminar(nodo->derecho,
                                     sucesor->bicicleta.getId(),
                                     eliminada);
        }

        return nodo;
    }

public:
    ArbolBicicletas() : raiz(nullptr), cantidad(0) {
    }

    ~ArbolBicicletas() {
        liberar(raiz);
    }

    // evitamos copias superficiales de los punteros
    ArbolBicicletas(const ArbolBicicletas&) = delete;
    ArbolBicicletas& operator=(const ArbolBicicletas&) = delete;

    bool insertar(const Bicicleta& bicicleta) {
        bool insertada = false;
        raiz = insertar(raiz, bicicleta, insertada);

        if (insertada) {
            cantidad++;
        }

        return insertada;
    }

    // Devuelve puntero a la bici o nullptr si no existe
    const Bicicleta* buscar(int id) const {
        const Nodo* actual = raiz;

        while (actual != nullptr) {
            if (id == actual->bicicleta.getId()) {
                return &actual->bicicleta;
            }

            actual = (id < actual->bicicleta.getId()) ? actual->izquierdo
                                                      : actual->derecho;
        }

        return nullptr;
    }

    bool eliminar(int id) {
        bool eliminada = false;
        raiz = eliminar(raiz, id, eliminada);

        if (eliminada) {
            cantidad--;
        }

        return eliminada;
    }

    void listarInorder() const {
        inorder(raiz);
    }

    int contarAveriadas() const {
        return contarAveriadas(raiz);
    }

    int altura() const {
        return altura(raiz);
    }

    int listarMasDeKm(double km) const {
        return listarMasDeKm(raiz, km);
    }

    int getCantidad() const {
        return cantidad;
    }
};

#endif