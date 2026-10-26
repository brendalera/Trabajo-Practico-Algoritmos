# Sistema de Bicicletas Públicas

Trabajo Práctico de Algoritmos — UNAHUR

**Integrantes:** 
- Lera Centurión Brenda
- Arias Lavia Luana
- Bravo Álvaro


Sistema en C++ (orientado a objetos, memoria dinámica) que gestiona estaciones de bicicletas públicas de Buenos Aires, sus bicicletas, los viajes de los usuarios y la redistribución de bicicletas. Todas las estructuras (tabla hash, cola, heap, árbol, grafo) están implementadas a mano: no se usan `vector`, `map`, `unordered_map`, `queue`, `priority_queue` ni `set`.

## Compilación y ejecución

Desde la carpeta `SistemaDeBicicletas`:

```
g++ -std=c++17 -Wall -Wextra main.cpp Bicicleta.cpp Estacion.cpp TablaHash.cpp Viaje.cpp Redistribucion.cpp -o bicicletas
./bicicletas        (en Windows: .\bicicletas.exe)
```

El programa lee los archivos desde `archivos/`, por eso hay que ejecutarlo desde `SistemaDeBicicletas`.

Pruebas automáticas del árbol (tiene su propio `main`, se compila aparte):

```
g++ -std=c++17 -Wall -Wextra prueba.cpp Bicicleta.cpp -o prueba
./prueba
```

Verificación de memoria: `valgrind --leak-check=full ./bicicletas` (compilar con `-g`). Resultado: [completar tras correrlo].

## Archivos de entrada (`archivos/`)

| Archivo | Campos (uno por línea, separados por espacios) |
|---|---|
| `estaciones.txt` | codigo nombre barrio capacidad_anclajes bicis_disponibles |
| `bicicletas.txt` | bici_id codigo_estacion tipo estado kilometros |
| `viajes.txt` | viaje_id bici_id dni_usuario estacion_origen estacion_destino fecha duracion_min |
| `ciclovias.txt` | estacion_a estacion_b (conexión bidireccional) |

Las fechas tienen formato AAAAMMDD. Se asume que los archivos están bien formados.

## Módulos

| Módulo | Descripción |
|---|---|
| `Estacion` | Datos de una estación y si tiene menos del 20% de ocupación |
| `Bicicleta` | Datos de una bicicleta (`tipo`: Mecanica/Electrica, `estado`: OK/Averiada) |
| `Viaje` | Datos de un viaje |
| `TablaHash` | Estaciones indexadas por código. Encadenamiento con listas enlazadas. Cuenta colisiones y calcula el factor de carga |
| `OrdenamientoEstaciones` | Ordenamiento por inserción de un arreglo de estaciones |
| `Grafo` | Lista de adyacencia propia. Estaciones como nodos, ciclovías como aristas. Incluye el BFS |
| `ColeccionViajes` | Arreglo dinámico de viajes con las consultas B1 y B2 |
| `ColaEspera` | Cola FIFO (lista enlazada) de usuarios que esperan una bici |
| `GestorEspera` | Mantiene una `ColaEspera` por estación |
| `MinHeap` | Cola de prioridad del taller (min-heap en arreglo dinámico) |
| `ArbolBicicletas` | Árbol binario de búsqueda ordenado por `bici_id` |
| `Redistribucion` | Backtracking para elegir estaciones que suman la capacidad del camión |
| `main.cpp` | Carga de archivos y menú por consola |

## Menú

| Opción | Función |
|---|---|
| 1 | Mostrar estación por código |
| 2 / 3 | Agregar / eliminar estación |
| 4 | Recorrido con menos tramos entre dos estaciones (BFS) |
| 5 | Colisiones y factor de carga de la tabla hash |
| 6 | Buscar bicicleta por ID |
| 7 | Listar bicicletas ordenadas por ID (inorder) |
| 8 | Contar bicicletas averiadas |
| 9 | Altura del árbol |
| 10 | Bicicletas con más de X km |
| 11 | Listar estaciones ordenadas por capacidad o por bicis disponibles |
| 12 | Estaciones con menos del 20% de ocupación |
| 13 | Viajes desde una estación en un rango de fechas |
| 14 | Viajes de un usuario por DNI y total de minutos |
| 15 | Retirar una bici (si no hay, el usuario se encola) |
| 16 | Devolver una bici (se asigna al primero de la cola) |
| 17 | Ver la cola de espera de una estación |
| 18 | Enviar una bici averiada al taller |
| 19 | Atender la bici más urgente del taller |
| 20 | Redistribución con backtracking |

## Tabla hash: colisiones y factor de carga

- Tamaño de la tabla: 101 posiciones. Función hash: polinómica de base 31 sobre los caracteres del código, módulo 101. Las colisiones se resuelven con encadenamiento (lista enlazada por posición).
- Con los datos de prueba (7 estaciones: PLZ, PAL, CAB, RET, CON, BOE, SOL): **0 colisiones** y **factor de carga 7 / 101 ≈ 0,069**.
- Si se cambian los datos de `estaciones.txt`, se actualizan con la opción 5 del menú. [verificar con los datos finales]

## Consignas de análisis

### A. Gestión de estaciones

| Punto | Complejidad | Por qué esa estructura |
|---|---|---|
| Buscar, agregar y eliminar estación (tabla hash) | O(1) promedio, O(n) peor caso | El código identifica a cada estación, y la tabla hash va directo a la posición sin recorrer todas. En el peor caso todos los códigos caen en la misma lista. |
| Listar ordenadas (inserción) | O(n²) | La tabla hash no guarda orden, por eso se copian las estaciones a un arreglo y se ordena. Inserción es simple de explicar y alcanza para pocas estaciones. |
| Menos del 20% de ocupación | O(n) | Hay que revisar cada estación una vez. |
| Recorrido mínimo (BFS) | O(V + E) | BFS visita por niveles, así que la primera vez que llega al destino lo hizo con la menor cantidad de tramos. Se usó lista de adyacencia porque la red de ciclovías es rala: ocupa O(V + E) en lugar de O(V²) de una matriz. |

### B. Viajes y colas de espera

| Punto | Complejidad | Por qué esa estructura |
|---|---|---|
| B1. Viajes desde una estación en un rango de fechas | O(n) | Arreglo dinámico: los viajes solo se agregan al final y se recorren completos. No hay un orden que permita saltear registros. Las fechas AAAAMMDD se comparan como texto. |
| B2. Viajes por DNI y total de minutos | O(n) | Mismo motivo que B1: se recorren todos los viajes una vez. |
| B3. Bicicletas con más de X km | O(n) | Se recorre el árbol completo, porque la condición sobre kilómetros no coincide con el orden por ID y no permite descartar ramas. |
| B4. Cola de espera por estación | encolar y desencolar O(1) | Se necesita atender por orden de llegada, que es lo que da una cola FIFO. La lista enlazada con puntero al frente y al final evita recorrer o mover elementos. |
| B5. Cola de prioridad del taller (min-heap) | insertar y extraer O(log n), consultar la más urgente O(1) | Solo hace falta saber siempre cuál es la más urgente. Un arreglo ordenado costaría O(n) por inserción y uno sin ordenar O(n) por extracción; el heap equilibra ambas en O(log n). Si dos bicis tienen la misma prioridad, sale primero la que entró antes. |

Decisiones de B5: solo entran al taller bicicletas averiadas; las eléctricas entran siempre con prioridad 1; para las mecánicas el usuario elige de 1 (más urgente) a 3.

Decisión de B4: al devolver una bici en una estación con cola, se asigna directamente al primero de la cola y el contador de bicis disponibles no cambia.

### C. Árbol binario de búsqueda

| Operación | Complejidad |
|---|---|
| Insertar y buscar | O(log n) promedio, O(n) peor caso |
| Listar inorder, contar averiadas, altura, liberar (postorder) | O(n) |
| Eliminar (opcional, 3 casos) | O(log n) promedio, O(n) peor caso |

La liberación se hace en postorder porque hay que borrar los hijos antes que el padre; si se borrara primero el padre, se perderían los punteros a los hijos.

**Pregunta: ¿qué altura tendría el árbol si las bicicletas se cargaran ordenadas por ID? ¿Cómo afecta eso al costo de la búsqueda?**

Si se cargan las bicicletas 501, 502, 503, 504 y 505 en ese orden, cada una es mayor que todas las anteriores y siempre se inserta como hijo derecho del último nodo. El árbol queda como una lista enlazada: **altura 5**. Buscar el 505 cuesta 5 comparaciones, es decir O(n). En cambio, con las mismas cinco bicicletas cargadas en orden 503, 501, 502, 504, 505 la raíz sería 503 y la altura bajaría a 3. Un árbol balanceado cuesta O(log n) por búsqueda, y uno degenerado, O(n). Cargar datos ya ordenados es el peor caso.

### D. Redistribución con backtracking

Para cada estación hay dos opciones: llevarle bicicletas o no. El algoritmo prueba las dos, va sumando los faltantes y, cuando la suma llega exactamente a C, muestra esa combinación. Si al incluir una estación la suma se pasa de C, descarta esa rama (poda). Después de probar una opción, deshace la elección y prueba la otra.

**Complejidad en el peor caso: O(2ⁿ)**, con n estaciones, porque hay 2ⁿ subconjuntos posibles. La poda mejora el caso promedio pero no el peor caso.

Ejemplo del enunciado: C = 10 con PLZ 3, CAB 7, RET 5, CON 2, BOE 5 da las cuatro soluciones `{PLZ, CAB}`, `{PLZ, RET, CON}`, `{PLZ, CON, BOE}` y `{RET, BOE}`.

## Supuestos

- Los faltantes de la redistribución tienen que ser mayores a 0.
- Las colas de espera, el taller y los cambios hechos desde el menú viven solo en memoria: al cerrar el programa se pierden y los archivos `.txt` no se modifican.
- Al eliminar una estación se eliminan también sus ciclovías, pero no se reubican sus bicicletas.