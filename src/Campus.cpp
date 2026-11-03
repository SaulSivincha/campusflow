#include "campusflow/Campus.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace campusflow {

LugarId Campus::agregarLugar(std::string nombre) {
    if (nombre.empty()) {
        throw std::invalid_argument("El lugar necesita un nombre");
    }
    lugares_.push_back({std::move(nombre)});
    conexiones_.emplace_back();
    return lugares_.size() - 1;
}

void Campus::conectar(LugarId origen, LugarId destino, double metros, bool escaleras) {
    const auto& adyacentes = vecinos(origen);
    lugar(destino);
    if (origen == destino || !std::isfinite(metros) || metros <= 0) {
        throw std::invalid_argument("El tramo necesita lugares distintos y distancia positiva finita");
    }
    if (std::any_of(adyacentes.begin(), adyacentes.end(), [destino](const Tramo& tramo) {
            return tramo.destino == destino;
        })) {
        throw std::invalid_argument("Ya existe un tramo entre esos lugares");
    }
    conexiones_[origen].push_back({destino, metros, escaleras});
    conexiones_[destino].push_back({origen, metros, escaleras});
}

void Campus::bloquearTramo(LugarId origen, LugarId destino, bool bloqueado) {
    lugar(origen);
    lugar(destino);
    auto& adyacentes = conexiones_[origen];
    auto it = std::find_if(adyacentes.begin(), adyacentes.end(), [destino](const Tramo& tramo) {
        return tramo.destino == destino;
    });
    if (it == adyacentes.end()) {
        throw std::invalid_argument("No existe el tramo solicitado");
    }
    it->bloqueado = bloqueado;
    for (auto& tramo : conexiones_[destino]) {
        if (tramo.destino == origen) {
            tramo.bloqueado = bloqueado;
        }
    }
}

std::size_t Campus::cantidadLugares() const { return lugares_.size(); }
const Lugar& Campus::lugar(LugarId id) const { return lugares_.at(id); }
const std::vector<Tramo>& Campus::vecinos(LugarId id) const { return conexiones_.at(id); }

} // namespace campusflow
