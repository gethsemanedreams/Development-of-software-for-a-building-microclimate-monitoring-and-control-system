#include "TemperatureSensor.h"
#include <iostream>
#include <cstdlib>

TemperatureSensor::TemperatureSensor(const std::string& id, float min, float max)
	: Sensor(id, "Temperature", "∞C"), m_thresholdMin(min), m_thresholdMax(max)
{
}

TemperatureSensor::~TemperatureSensor()
{
	std::cout << "TemperatureSensor destroyed: " << m_id << std::endl;
}

float TemperatureSensor::ReadValue()
{
	// Ёмул€ци€ случайного измерени€ температуры
	m_lastValue = static_cast<float>(rand() % 60 - 10);
	std::cout << "Temperature: " << m_lastValue << " ∞C" << std::endl;
	return m_lastValue;
}

bool TemperatureSensor::IsOutOfRange() const
{
	return (m_lastValue < m_thresholdMin || m_lastValue > m_thresholdMax);
}

std::string TemperatureSensor::GetWarningLevel() const
{
	if (IsOutOfRange()) return "CRITICAL";
	return "NORMAL";
}