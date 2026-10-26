#include <iostream>
#include "ArbolBicicletas.h"

int fallos = 0;

void verificar(bool condicion, const std::string& descripcion) {
    if (condicion) {
        std::cout << "[OK]    " << descripcion << std::endl;
    } else {
        std::cout << "[FALLO] " << descripcion << std::endl;
        fallos++;
    }
}

Bicicleta crearBici(int id, const std::string& estado, double km) {
    return Bicicleta(id, "PLZ", "Mecanica", estado, km);
}

int main() {
    // Arbol vacio
    std::cout << "\n- Arbol vacio -" << std::endl;
    {
        ArbolBicicletas vacio;
        verificar(vacio.altura() == 0, "altura de arbol vacio es 0");
        verificar(vacio.contarAveriadas() == 0, "averiadas en arbol vacio es 0");
        verificar(vacio.buscar(1) == nullptr, "buscar en arbol vacio devuelve nullptr");
        verificar(!vacio.eliminar(1), "eliminar en arbol vacio devuelve false");
    }

    // 5 bicis cargadas ordenadas
    std::cout << "\n== 5 bicis ordenadas por ID ==" << std::endl;
    {
        ArbolBicicletas lista;
        lista.insertar(crearBici(501, "OK", 1240));
        lista.insertar(crearBici(502, "Averiada", 3810));
        lista.insertar(crearBici(503, "OK", 560));
        lista.insertar(crearBici(504, "Averiada", 4200));
        lista.insertar(crearBici(505, "OK", 90));

        verificar(lista.getCantidad() == 5, "cantidad = 5");
        verificar(lista.altura() == 5, "altura = 5 (el arbol queda como una lista)");
        verificar(lista.contarAveriadas() == 2, "averiadas = 2");
        verificar(lista.buscar(503) != nullptr, "buscar 503 la encuentra");
        verificar(lista.buscar(999) == nullptr, "buscar 999 devuelve nullptr");
        verificar(!lista.insertar(crearBici(501, "OK", 1)), "insertar ID repetido devuelve false");
        verificar(lista.getCantidad() == 5, "la cantidad no cambia con el repetido");

        std::cout << "- Bicis con mas de 1000 km:" << std::endl;
        int masDeMil = lista.listarMasDeKm(1000);
        verificar(masDeMil == 3, "hay 3 bicis con mas de 1000 km (501, 502, 504)");
    }

    // Arbol balanceado y eliminacion
    std::cout << "\n- Arbol balanceado y eliminacion -" << std::endl;
    {
        // Forma del arbol:        50
        //                      30     70
        //                    20  40 60  80
        ArbolBicicletas arbol;
        int ids[] = {50, 30, 70, 20, 40, 60, 80};

        for (int id : ids) {
            arbol.insertar(crearBici(id, "OK", 100));
        }

        verificar(arbol.getCantidad() == 7, "cantidad = 7");
        verificar(arbol.altura() == 3, "altura = 3 (balanceado)");

        // Caso 1: hoja
        verificar(arbol.eliminar(20), "eliminar 20 (hoja) devuelve true");
        verificar(arbol.buscar(20) == nullptr, "20 ya no esta");
        verificar(arbol.getCantidad() == 6, "cantidad = 6");

        // Caso 2: un hijo (30 ahora solo tiene a 40)
        verificar(arbol.eliminar(30), "eliminar 30 (un hijo) devuelve true");
        verificar(arbol.buscar(30) == nullptr, "30 ya no esta");
        verificar(arbol.buscar(40) != nullptr, "40 sigue estando");
        verificar(arbol.getCantidad() == 5, "cantidad = 5");

        // Caso 3: dos hijos (la raiz)
        verificar(arbol.eliminar(50), "eliminar 50 (dos hijos) devuelve true");
        verificar(arbol.buscar(50) == nullptr, "50 ya no esta");
        verificar(arbol.buscar(40) != nullptr, "40 sigue estando");
        verificar(arbol.buscar(60) != nullptr, "60 sigue estando");
        verificar(arbol.buscar(70) != nullptr, "70 sigue estando");
        verificar(arbol.buscar(80) != nullptr, "80 sigue estando");
        verificar(arbol.getCantidad() == 4, "cantidad = 4");

        verificar(!arbol.eliminar(999), "eliminar inexistente devuelve false");
        verificar(arbol.getCantidad() == 4, "la cantidad no cambia");

        std::cout << "- Inorder (tiene que salir 40, 60, 70, 80):" << std::endl;
        arbol.listarInorder();
    }

    std::cout << "\n==============================" << std::endl;
    if (fallos == 0) {
        std::cout << "TODAS LAS PRUEBAS PASARON" << std::endl;
    } else {
        std::cout << "PRUEBAS FALLIDAS: " << fallos << std::endl;
    }

    return fallos;
}