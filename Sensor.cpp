#include "Sensor.hpp"
#include <iostream>

Sensor::Sensor() : m_id("0"), m_name("Unknown"), m_unit("-"), m_lastValue(0.0f), m_status("OK") {}

Sensor::Sensor(const std::string& id, const std::string& name, const std::string& unit)
	: m_id(id), m_name(name), m_unit(unit), m_lastValue(0.0f), m_status("OK") {
}

Sensor::~Sensor() {}

bool Sensor::CheckStatus()
{
	std::cout << "Checking sensor status: " << m_name << std::endl;
	return true;
}

void Sensor::Calibrate()
{
	std::cout << "Calibrating sensor: " << m_name << std::endl;
}