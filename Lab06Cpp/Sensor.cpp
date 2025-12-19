#include "Sensor.hpp"

Sensor::Sensor(const std::string& id,
               const std::string& name,
               const std::string& unit)
    : m_id(id)
    , m_name(name)
    , m_unit(unit)
    , m_lastValue(0.0f)
    , m_status("OK")
{
}

bool Sensor::CheckStatus() const
{
    std::cout << "Checking status of sensor '" << m_name
              << "': status = " << m_status << std::endl;
    return m_status == "OK";
}

void Sensor::Calibrate()
{
    std::cout << "Base calibration for sensor '" << m_name << "'" << std::endl;
}

std::string Sensor::Describe() const
{
    return "Sensor[" + m_id + "] '" + m_name + "' (" + m_unit + ")";
}

void Sensor::PrintWithHeader() const
{
    std::cout << "[Sensor info] " << Describe() << std::endl;
}

std::string Sensor::TypeName() const
{
    // Невиртуальная функция: при вызове через Sensor* будет использоваться
    // именно эта реализация, даже если в потомке есть функция с тем же именем.
    return "BaseSensor";
}

Sensor& Sensor::SetStatus(const std::string& status)
{
    this->m_status = status; // Явное использование this.
    return *this;
}
