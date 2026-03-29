#include "MonitoringSystem.hpp"
#include "Logger.hpp"
#include <iostream>

void MonitoringSystem::PollSensors()
{
    Logger::Instance().Log("MonitoringSystem: start polling all rooms");
    std::cout << "MonitoringSystem: polling all rooms..." << std::endl;

    for (const auto& room : m_rooms)
    {
        if (!room)
            continue;

        Logger::Instance().Log("Polling room: " + room->GetName());
        room->CheckAllSensors();
    }

    Logger::Instance().Log("MonitoringSystem: finish polling all rooms");
}
