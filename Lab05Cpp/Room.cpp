#include "Room.hpp"
#include <iostream>

Room::Room(const std::string& name)
    : m_name(name)
{
}

Room::Room(const Room& other)
    : m_name(other.m_name)
    , m_sensors(other.m_sensors) // копируем shared_ptr – датчики разделяются между комнатами
{
}

void Room::AddSensor(const SensorPtr& sensor)
{
    m_sensors.push_back(sensor);
}

SensorPtr Room::FindSensorById(const std::string& id) const
{
    for (const auto& s : m_sensors)
    {
        // Пример работы со строками: ищем id как подстроку.
        if (s->GetId().find(id) != std::string::npos)
        {
            return s;
        }
    }
    return nullptr;
}

SensorPtr Room::operator[](std::size_t index) const
{
    if (index >= m_sensors.size())
    {
        throw std::out_of_range("Room::operator[]: индекс вне диапазона");
    }
    return m_sensors[index];
}

std::ostream& operator<<(std::ostream& os, const Room& room)
{
    os << "Room{" << room.m_name << ", sensors=" << room.m_sensors.size() << "}";
    return os;
}

