#include "campusflow/Ruta.hpp"

#include <iostream>
#include <memory>

using namespace campusflow;

void mostrar(const Campus& campus, const IEstrategiaRuta& estrategia,
             LugarId origen, LugarId destino) {
    const auto ruta = estrategia.calcular(campus, origen, destino);
    if (!ruta) {
        std::cout << "Sin ruta disponible.\n";
        return;
    }
    for (std::size_t i = 0; i < ruta->lugares.size(); ++i) {
        if (i > 0) {
            std::cout << " -> ";
        }
        std::cout << campus.lugar(ruta->lugares[i]).nombre;
    }
    std::cout << " (" << ruta->metros << " m)\n";
}

int main() {
    Campus campus;
    const auto entrada = campus.agregarLugar("Entrada");
    const auto patio = campus.agregarLugar("Patio");
    const auto rampa = campus.agregarLugar("Rampa");
    const auto pabellon = campus.agregarLugar("Pabellon");
    const auto biblioteca = campus.agregarLugar("Biblioteca");
    campus.conectar(entrada, patio, 80);
    campus.conectar(patio, pabellon, 40, true);
    campus.conectar(entrada, rampa, 100);
    campus.conectar(rampa, pabellon, 80);

    std::cout << "CampusFlow - Primer avance (mapa ficticio)\n\nRuta mas corta:\n";
    std::unique_ptr<IEstrategiaRuta> estrategia = std::make_unique<RutaMasCorta>();
    mostrar(campus, *estrategia, entrada, pabellon);

    std::cout << "\nRuta accesible (sin escaleras):\n";
    estrategia = std::make_unique<RutaAccesible>();
    mostrar(campus, *estrategia, entrada, pabellon);

    std::cout << "\nRuta mas corta tras bloquear Patio - Pabellon:\n";
    campus.bloquearTramo(patio, pabellon);
    estrategia = std::make_unique<RutaMasCorta>();
    mostrar(campus, *estrategia, entrada, pabellon);

    std::cout << "\nBiblioteca todavia sin conexion:\n";
    mostrar(campus, *estrategia, entrada, biblioteca);
}
