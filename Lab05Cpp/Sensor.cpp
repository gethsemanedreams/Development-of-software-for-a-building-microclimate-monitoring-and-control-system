#include "Sensor.hpp"
#include <iostream>

Sensor::Sensor(const std::string& id,
               const std::string& name,
               const std::string& unit)
    : m_id(id)
    , m_name(name)
    , m_unit(unit)
{
}

Sensor::Sensor(const Sensor& other)
    : m_id(other.m_id)
    , m_name(other.m_name)
    , m_unit(other.m_unit)
    , m_lastValue(other.m_lastValue)
    , m_status(other.m_status)
{
}

bool Sensor::CheckStatus() const
{
    return m_status == "OK";
}

void Sensor::Calibrate()
{
    std::cout << "Calibrating sensor " << m_id << " (" << m_name << ")\n";
}

Sensor& Sensor::SetStatus(const std::string& status)
{
    this->m_status = status; // Явное использование this.
    return *this;            // Возвращаем *this для цепочек вызовов.
}

