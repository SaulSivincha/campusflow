# CampusFlow

Primer avance de Tecnología de Objetos: prototipo en **C++17** para comparar
rutas cortas y accesibles en un campus universitario.

## Objetivo

Modelar lugares y caminos, evitando escaleras cuando el usuario necesita
una ruta accesible. El mapa de demostración es ficticio y no representa
las condiciones reales de accesibilidad de la UNSA.

## Compilar y ejecutar

Requisitos: CMake 3.16 o superior y un compilador con soporte para C++17.

```bash
cmake -S . -B build
cmake --build build
./build/campusflow
```

## Qué incluye este avance

- Cinco lugares ficticios y cuatro caminos bidireccionales.
- Ruta más corta mediante Dijkstra y ruta accesible evitando escaleras.
- Bloqueo y desbloqueo de caminos; detección de destinos sin conexión.
- Demostración fija por consola, sin dependencias externas.

En este modelo inicial, «accesible» significa únicamente «sin escaleras».
La pendiente, el ancho y otras condiciones se considerarían en una ampliación.

Salida de la demostración:

```text
Ruta mas corta:
Entrada -> Patio -> Pabellon (120 m)

Ruta accesible (sin escaleras):
Entrada -> Rampa -> Pabellon (180 m)

Ruta mas corta tras bloquear Patio - Pabellon:
Entrada -> Rampa -> Pabellon (180 m)

Biblioteca todavia sin conexion:
Sin ruta disponible.
```

## Relación con el curso

| Tema | Evidencia |
| --- | --- |
| Clases y encapsulamiento | `Campus` administra lugares y conexiones privados. |
| Clases abstractas, herencia y polimorfismo | `IEstrategiaRuta`, `RutaMasCorta` y `RutaAccesible`. |
| Destructores y punteros inteligentes | Destructor virtual y `std::unique_ptr` en la demostración. |
| STL, lambdas y métodos `const` | Vectores, cola de prioridad, filtros y consultas del modelo. |
| Excepciones | Validación de distancias, identificadores y conexiones. |
| Plantillas y pruebas | Ayudante genérico `debeFallar` y pruebas con CTest. |
| SOLID y GRASP | Separación del modelo, cálculo de rutas y presentación. |
| CMake y Git | Compilación y desarrollo por etapas. |

Las pruebas verifican rutas, restricciones, bloqueos en ambos sentidos,
desbloqueos, lugares aislados y datos inválidos. No necesitan bibliotecas adicionales.

```bash
ctest --test-dir build --output-on-failure
```

## Siguiente avance

Incorporar persistencia del mapa y selección de origen y destino por el usuario.
Después se evaluará una interfaz 2D y una simulación básica de congestión.
Estas funciones todavía no están implementadas.
