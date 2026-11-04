#pragma once

#include "campusflow/Campus.hpp"

#include <optional>

namespace campusflow {

struct Ruta {
    std::vector<LugarId> lugares;
    double metros;
};

class IEstrategiaRuta {
public:
    virtual ~IEstrategiaRuta() = default;
    virtual std::optional<Ruta> calcular(const Campus& campus, LugarId origen,
                                         LugarId destino) const = 0;
};

class RutaMasCorta final : public IEstrategiaRuta {
public:
    std::optional<Ruta> calcular(const Campus& campus, LugarId origen,
                                 LugarId destino) const override;
};

class RutaAccesible final : public IEstrategiaRuta {
public:
    std::optional<Ruta> calcular(const Campus& campus, LugarId origen,
                                 LugarId destino) const override;
};

} // namespace campusflow
