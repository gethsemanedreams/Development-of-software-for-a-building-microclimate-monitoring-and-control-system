#include "HumiditySensor.hpp"
#include <stdexcept>
#include <iomanip>

HumiditySensor::HumiditySensor(const std::string& id,
                               const std::string& name,
                               float min,
                               float max)
    : Sensor(id, name, "%")
    , m_min(min)
    , m_max(max)
{
    if (min >= max)
    {
        throw std::invalid_argument("HumiditySensor: min threshold must be < max threshold");
    }
}

float HumiditySensor::ReadValue()
{
    static std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<float> dist(m_min - 20.0f, m_max + 20.0f);

    m_lastValue = dist(gen);
    std::cout << "HumiditySensor '" << m_name
              << "' read value: " << std::fixed << std::setprecision(2)
              << m_lastValue << " " << m_unit << std::endl;
    return m_lastValue;
}

bool HumiditySensor::CheckStatus() const
{
    bool ok = (m_lastValue >= m_min && m_lastValue <= m_max);
    std::cout << "HumiditySensor '" << m_name << "' status: "
              << (ok ? "OK" : "OUT OF RANGE") << std::endl;
    return ok;
}

void HumiditySensor::Calibrate()
{
    // ЛР-6: переопределение метода БЕЗ вызова базовой реализации.
    std::cout << "HumiditySensor '" << m_name << "': fast calibration without base call" << std::endl;
}

std::string HumiditySensor::Describe() const
{
    return "HumiditySensor[" + m_id + "] '" + m_name + "', range = " +
           std::to_string(m_min) + ".." + std::to_string(m_max) + " " + m_unit;
}

Sensor* HumiditySensor::Clone() const
{
    return new HumiditySensor(*this);
}
