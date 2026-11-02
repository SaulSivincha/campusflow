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

## Organización del avance

El historial se organiza retrospectivamente en cinco etapas con fechas
asignadas del 2 al 6 de noviembre de 2026 (zona horaria de Lima).
Estas fechas representan la organización del avance y no acreditan trabajo
realizado en esos días; este prototipo se preparó el 8 de noviembre de 2026.

| Etapa | Fecha asignada | Entregable |
| --- | --- | --- |
| 1 | Lunes 02/11 | Estructura del proyecto y CMake |
| 2 | Martes 03/11 | Modelo de lugares y caminos |
| 3 | Miércoles 04/11 | Estrategias de cálculo de rutas |
| 4 | Jueves 05/11 | Demostración por consola |
| 5 | Viernes 06/11 | Pruebas y documentación del avance |
