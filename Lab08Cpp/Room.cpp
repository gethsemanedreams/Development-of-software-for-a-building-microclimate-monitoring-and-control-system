#include "Room.hpp"
#include <iostream>

void Room::CheckAllSensors()
{
    std::cout << "Checking sensors in room '" << m_name << "'..." << std::endl;
    for (const auto& s : m_sensors)
    {
        if (!s)
            continue;

        s->ReadValue();
        s->CheckStatus();
    }
}

std::shared_ptr<Room> Room::ShallowClone() const
{
    auto clone = std::make_shared<Room>(*this); // копируем name и вектор указателей
    std::cout << "Room '" << m_name << "' shallow-cloned." << std::endl;
    return clone;
}

std::shared_ptr<Room> Room::DeepClone() const
{
    auto clone = std::make_shared<Room>(m_name);
    for (const auto& s : m_sensors)
    {
        if (s)
        {
            clone->AddSensor(SensorPtr(s->Clone())); // новый Sensor с тем же состоянием
        }
    }
    std::cout << "Room '" << m_name << "' deep-cloned." << std::endl;
    return clone;
}
