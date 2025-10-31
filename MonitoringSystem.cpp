#include "MonitoringSystem.h"
#include <iostream>

MonitoringSystem::MonitoringSystem() = default;

MonitoringSystem::~MonitoringSystem()
{
	// Очистка динамически созданных помещений.
	for (auto r : m_rooms)
		delete r;
}

void MonitoringSystem::AddRoom(Room* room)
{
	m_rooms.push_back(room);
}

void MonitoringSystem::PollSensors()
{
	std::cout << "Polling all sensors..." << std::endl;
	for (auto r : m_rooms)
	{
		r->CheckAllSensors();
		m_logger.Write("Polled room successfully");
	}
}