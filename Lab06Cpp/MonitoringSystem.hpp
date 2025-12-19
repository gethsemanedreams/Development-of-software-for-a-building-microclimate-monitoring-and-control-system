#pragma once
#include <vector>
#include "Room.hpp"

/// \brief Система мониторинга, которая хранит набор помещений.
///
/// ЛР-6: запрещаем копирование (конструктор копирования по умолчанию
/// был бы сгенерирован, но мы явно блокируем его).
class MonitoringSystem
{
    std::vector<RoomPtr> m_rooms;

public:
    MonitoringSystem() = default;

    // ЛР-6: запрещаем копирование системы.
    MonitoringSystem(const MonitoringSystem&) = delete;
    MonitoringSystem& operator=(const MonitoringSystem&) = delete;

    void AddRoom(const RoomPtr& room)
    {
        m_rooms.push_back(room);
    }

    void PollSensors();
};
