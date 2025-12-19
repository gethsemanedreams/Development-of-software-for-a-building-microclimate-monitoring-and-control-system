#pragma once
#include "Sensor.hpp"
#include <random>

/// \brief Датчик влажности.
/// Ещё один производный класс от Sensor.
///
/// ЛР-6:
///  * демонстрируем второй пример наследования;
///  * переопределяем виртуальные методы;
///  * в Calibrate() НЕ вызываем базовую реализацию Sensor::Calibrate().
class HumiditySensor : public Sensor
{
protected:
    float m_min{};
    float m_max{};

public:
    HumiditySensor(const std::string& id,
                   const std::string& name,
                   float min,
                   float max);

    ~HumiditySensor() override = default;

    float ReadValue() override;
    bool  CheckStatus() const override;
    void  Calibrate() override;
    std::string Describe() const override;
    Sensor* Clone() const override;
};
