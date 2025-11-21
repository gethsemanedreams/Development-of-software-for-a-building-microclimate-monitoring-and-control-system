#include "MonitoringSystem.hpp"
#include "Logger.hpp"
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

    // Логгируем начало опроса
    Logger::GetInstance().Log("Started polling all sensors");

    for (auto r : m_rooms)
    {
        r->CheckAllSensors();

        // Логгируем успешный опрос комнаты
        Logger::GetInstance().Log("Polled room: " + r->GetName());
    }

    Logger::GetInstance().Log("Finished polling all sensors");
}