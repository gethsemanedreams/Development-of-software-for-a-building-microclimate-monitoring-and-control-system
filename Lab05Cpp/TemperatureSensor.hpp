#pragma once
#include "Sensor.hpp"
#include <stdexcept>

/// \brief Датчик температуры.
/// Наследуется от Sensor. В конструкторе явно вызываем конструктор базового
/// класса Sensor (требование ЛР-5 по наследованию).
///
/// Здесь также демонстрируем генерацию исключений (throw), если
/// задан некорректный диапазон температур.
class TemperatureSensor : public Sensor
{
private:
    float m_minThreshold;
    float m_maxThreshold;

public:
    TemperatureSensor(const std::string& id,
                      const std::string& name,
                      float minThreshold,
                      float maxThreshold);

    TemperatureSensor(const TemperatureSensor& other);

    float GetMinThreshold() const { return m_minThreshold; }
    float GetMaxThreshold() const { return m_maxThreshold; }

    /// Псевдо-чтение значения: просто возвращаем уже сохранённое значение.
    float ReadValue() override;

    /// Установка нового значения с проверкой на выход за диапазон.
    void UpdateValue(float value);

    /// Проверка, является ли значение аномальным.
    bool IsAnomalous() const;
};

using TemperatureSensorPtr = std::shared_ptr<TemperatureSensor>;

