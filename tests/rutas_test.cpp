#include "campusflow/Ruta.hpp"

#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace campusflow;

void verificar(bool condicion, const char* mensaje) {
    if (!condicion) {
        throw std::runtime_error(mensaje);
    }
}

template <typename Excepcion, typename Operacion>
void debeFallar(Operacion operacion) {
    try {
        operacion();
    } catch (const Excepcion&) {
        return;
    }
    throw std::runtime_error("Se esperaba una excepcion de validacion");
}

int main() {
    try {
        Campus campus;
        const auto a = campus.agregarLugar("Entrada");
        const auto b = campus.agregarLugar("Patio");
        const auto c = campus.agregarLugar("Rampa");
        const auto d = campus.agregarLugar("Pabellon");
        const auto aislado = campus.agregarLugar("Biblioteca");
        campus.conectar(a, b, 80);
        campus.conectar(b, d, 40, true);
        campus.conectar(a, c, 100);
        campus.conectar(c, d, 80);
        RutaMasCorta corta;
        RutaAccesible accesible;

        const auto ruta = corta.calcular(campus, a, d);
        verificar(ruta && ruta->metros == 120 && ruta->lugares == std::vector<LugarId>{a, b, d},
                  "La ruta corta debe usar el patio");
        const auto sinEscaleras = accesible.calcular(campus, a, d);
        verificar(sinEscaleras && sinEscaleras->metros == 180 &&
                      sinEscaleras->lugares == std::vector<LugarId>{a, c, d},
                  "La ruta accesible debe usar la rampa");

        campus.bloquearTramo(b, d);
        const auto alternativa = corta.calcular(campus, a, d);
        const auto inversa = corta.calcular(campus, d, a);
        verificar(alternativa && alternativa->metros == 180 && inversa && inversa->metros == 180,
                  "El bloqueo debe aplicarse en ambos sentidos");
        campus.bloquearTramo(b, d, false);
        verificar(corta.calcular(campus, a, d)->metros == 120, "Debe permitir desbloquear");
        verificar(!corta.calcular(campus, a, aislado), "Debe detectar destinos aislados");
        const auto mismo = accesible.calcular(campus, a, a);
        verificar(mismo && mismo->metros == 0 && mismo->lugares == std::vector<LugarId>{a},
                  "Origen igual a destino debe tener distancia cero");

        campus.bloquearTramo(a, c);
        verificar(!accesible.calcular(campus, a, d), "Debe detectar que no hay ruta accesible");
        debeFallar<std::out_of_range>([&] { corta.calcular(campus, 999, d); });
        debeFallar<std::invalid_argument>([&] { campus.conectar(a, aislado, -1); });
        debeFallar<std::invalid_argument>([&] {
            campus.conectar(a, aislado, std::numeric_limits<double>::quiet_NaN());
        });
        debeFallar<std::invalid_argument>([&] {
            campus.conectar(a, aislado, std::numeric_limits<double>::infinity());
        });
        debeFallar<std::invalid_argument>([&] { campus.conectar(a, b, 80); });
        debeFallar<std::invalid_argument>([&] { campus.bloquearTramo(a, aislado); });
        std::cout << "Pruebas de rutas y validacion correctas.\n";
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
