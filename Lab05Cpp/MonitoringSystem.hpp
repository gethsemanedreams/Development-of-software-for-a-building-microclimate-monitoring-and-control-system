#pragma once
#include <vector>
#include <memory>
#include "Room.hpp"
#include "Logger.hpp"
#include "Measurement.hpp"
#include "Alert.hpp"
#include "User.hpp"

/// \brief Центральная система мониторинга.
///
/// Здесь показываем:
///  * использование std::shared_ptr / std::unique_ptr;
///  * обработку исключений при работе с датчиками.
class MonitoringSystem
{
private:
    std::vector<RoomPtr> m_rooms;
    std::shared_ptr<User> m_user;
    Logger m_logger;

public:
    MonitoringSystem();
    MonitoringSystem(const MonitoringSystem& other);

    void SetUser(const std::shared_ptr<User>& user);

    void AddRoom(const RoomPtr& room);

    /// \brief Опрос всех датчиков во всех комнатах.
    void PollSensors();

    /// \brief Возвращает ссылку на внутренний логгер.
    Logger& GetLogger() { return m_logger; }
};

