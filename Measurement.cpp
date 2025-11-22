#include "Measurement.hpp"

Measurement::Measurement(const std::string& sensorId, float value, const std::string& timestamp)
	: m_sensorId(sensorId), m_value(value), m_timestamp(timestamp)
{
	std::cout << "Measurement created for sensor: " << sensorId << std::endl;
}

Measurement::~Measurement()
{
	std::cout << "Measurement destroyed: " << m_sensorId << std::endl;
}

bool Measurement::IsAnomalous(float min, float max) const
{
	return (m_value < min || m_value > max);
}

std::string Measurement::ToString() const
{
	return "Sensor " + m_sensorId + " | Value: " + std::to_string(m_value) + " | Time: " + m_timestamp;
}
