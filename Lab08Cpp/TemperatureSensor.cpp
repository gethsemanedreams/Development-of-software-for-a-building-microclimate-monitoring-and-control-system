#include "TemperatureSensor.hpp"
#include <stdexcept>
#include <iomanip>

TemperatureSensor::TemperatureSensor(const std::string& id,
                                     const std::string& name,
                                     float min,
                                     float max)
    : Sensor(id, name, "°C")
    , m_min(min)
    , m_max(max)
{
    if (min >= max)
    {
        throw std::invalid_argument("TemperatureSensor: min threshold must be < max threshold");
    }
}

float TemperatureSensor::ReadValue()
{
    // Простая генерация псевдослучайной температуры.
    static std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<float> dist(m_min - 10.0f, m_max + 10.0f);

    m_lastValue = dist(gen);
    std::cout << "TemperatureSensor '" << m_name
              << "' read value: " << std::fixed << std::setprecision(2)
              << m_lastValue << " " << m_unit << std::endl;
    return m_lastValue;
}

bool TemperatureSensor::CheckStatus() const
{
    bool ok = (m_lastValue >= m_min && m_lastValue <= m_max);
    std::cout << "TemperatureSensor '" << m_name << "' status: "
              << (ok ? "OK" : "OUT OF RANGE") << std::endl;
    return ok;
}

void TemperatureSensor::Calibrate()
{
    // ЛР-6: пример переопределения метода базового класса с вызовом base-реализации.
    std::cout << "TemperatureSensor '" << m_name << "': custom calibration..." << std::endl;
    Sensor::Calibrate(); // Вызов базового варианта.
}

std::string TemperatureSensor::Describe() const
{
    return "TemperatureSensor[" + m_id + "] '" + m_name + "', range = " +
           std::to_string(m_min) + ".." + std::to_string(m_max) + " " + m_unit;
}

Sensor* TemperatureSensor::Clone() const
{
    // Поверхностное клонирование по данным: здесь оно эквивалентно копированию,
    // так как нет вложенных указателей.
    return new TemperatureSensor(*this);
}

TemperatureSensor& TemperatureSensor::operator=(const Sensor& base)
{
    if (this != &base)
    {
        // ЛР-6: пример присваивания объекту производного класса
        // состояния объекта базового класса.
        m_id     = base.GetId();
        m_name   = base.GetName();
        m_unit   = base.GetUnit();
        m_lastValue = base.GetLastValue();
        m_status = base.GetStatus();

        // Диапазон температур оставим прежним (или можно задать по умолчанию).
    }
    return *this;
}

std::string TemperatureSensor::TypeName() const
{
    return "TemperatureSensor";
}
