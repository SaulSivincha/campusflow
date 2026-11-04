#include "campusflow/Ruta.hpp"

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <utility>

namespace campusflow {
namespace {

std::optional<Ruta> buscar(const Campus& campus, LugarId origen, LugarId destino,
                          bool evitarEscaleras) {
    campus.lugar(origen);
    campus.lugar(destino);
    const auto cantidad = campus.cantidadLugares();
    const auto infinito = std::numeric_limits<double>::infinity();
    std::vector<double> distancias(cantidad, infinito);
    std::vector<LugarId> anteriores(cantidad, cantidad);
    using Pendiente = std::pair<double, LugarId>;
    std::priority_queue<Pendiente, std::vector<Pendiente>, std::greater<Pendiente>> pendientes;

    distancias[origen] = 0;
    pendientes.emplace(0, origen);
    while (!pendientes.empty()) {
        const auto [distancia, actual] = pendientes.top();
        pendientes.pop();
        if (distancia > distancias[actual]) {
            continue;
        }
        if (actual == destino) {
            break;
        }
        for (const auto& tramo : campus.vecinos(actual)) {
            if (tramo.bloqueado || (evitarEscaleras && tramo.escaleras)) {
                continue;
            }
            const double nueva = distancia + tramo.metros;
            if (nueva < distancias[tramo.destino]) {
                distancias[tramo.destino] = nueva;
                anteriores[tramo.destino] = actual;
                pendientes.emplace(nueva, tramo.destino);
            }
        }
    }
    if (distancias[destino] == infinito) {
        return std::nullopt;
    }
    Ruta ruta{{}, distancias[destino]};
    for (LugarId actual = destino; actual != cantidad; actual = anteriores[actual]) {
        ruta.lugares.push_back(actual);
    }
    std::reverse(ruta.lugares.begin(), ruta.lugares.end());
    return ruta;
}

} // namespace

std::optional<Ruta> RutaMasCorta::calcular(const Campus& campus, LugarId origen,
                                          LugarId destino) const {
    return buscar(campus, origen, destino, false);
}

std::optional<Ruta> RutaAccesible::calcular(const Campus& campus, LugarId origen,
                                          LugarId destino) const {
    return buscar(campus, origen, destino, true);
}

} // namespace campusflow
