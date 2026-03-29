#pragma once
#include <string>
#include <iostream>

/// \brief Одно измерение, полученное с датчика.
class Measurement
{
    std::string m_sensorId;
    float       m_value{};
    std::string m_timestamp;

public:
    Measurement(const std::string& sensorId,
                float value,
                const std::string& timestamp)
        : m_sensorId(sensorId)
        , m_value(value)
        , m_timestamp(timestamp)
    {
        std::cout << "Measurement created for sensor " << m_sensorId << std::endl;
    }

    Measurement(const Measurement&) = default;

    bool IsAnomalous(float min, float max) const
    {
        return m_value < min || m_value > max;
    }

    std::string ToString() const
    {
        return "Sensor " + m_sensorId + " | value = " + std::to_string(m_value) +
               " | time = " + m_timestamp;
    }
};
