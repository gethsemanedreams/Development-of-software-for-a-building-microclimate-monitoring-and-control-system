#include "TemperatureSensor.hpp"
#include <iostream>

TemperatureSensor::TemperatureSensor(const std::string& id,
                                     const std::string& name,
                                     float minThreshold,
                                     float maxThreshold)
    : Sensor(id, name, "°C") // Вызов конструктора базового класса.
    , m_minThreshold(minThreshold)
    , m_maxThreshold(maxThreshold)
{
    if (minThreshold >= maxThreshold)
    {
        // Демонстрация инициализации исключения (throw).
        throw std::invalid_argument(
            "Минимальный порог температуры должен быть меньше максимального.");
    }
}

TemperatureSensor::TemperatureSensor(const TemperatureSensor& other)
    : Sensor(other)
    , m_minThreshold(other.m_minThreshold)
    , m_maxThreshold(other.m_maxThreshold)
{
}

float TemperatureSensor::ReadValue()
{
    return m_lastValue;
}

void TemperatureSensor::UpdateValue(float value)
{
    m_lastValue = value;
}

bool TemperatureSensor::IsAnomalous() const
{
    return m_lastValue < m_minThreshold || m_lastValue > m_maxThreshold;
}

