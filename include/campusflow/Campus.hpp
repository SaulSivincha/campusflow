#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace campusflow {

using LugarId = std::size_t;

struct Lugar {
    std::string nombre;
};

struct Tramo {
    LugarId destino;
    double metros;
    bool escaleras;
    bool bloqueado = false;
};

class Campus {
public:
    LugarId agregarLugar(std::string nombre);
    void conectar(LugarId origen, LugarId destino, double metros, bool escaleras = false);
    void bloquearTramo(LugarId origen, LugarId destino, bool bloqueado = true);

    std::size_t cantidadLugares() const;
    const Lugar& lugar(LugarId id) const;
    const std::vector<Tramo>& vecinos(LugarId id) const;

private:
    std::vector<Lugar> lugares_;
    std::vector<std::vector<Tramo>> conexiones_;
};

} // namespace campusflow
