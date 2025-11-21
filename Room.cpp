#include "Room.hpp"
#include <iostream>

Room::Room(const std::string& name) : m_name(name) {}

Room::~Room()
{
	// Удаление всех динамически созданных датчиков.
	for (auto s : m_sensors)
		delete s;
}

void Room::AddSensor(Sensor* sensor)
{
	m_sensors.push_back(sensor);
}

void Room::CheckAllSensors()
{
	std::cout << "Checking sensors in room: " << m_name << std::endl;
	for (auto s : m_sensors)
	{
		s->ReadValue();
		s->CheckStatus();
	}
}

std::string Room::GetName() const
{
	return m_name;
}