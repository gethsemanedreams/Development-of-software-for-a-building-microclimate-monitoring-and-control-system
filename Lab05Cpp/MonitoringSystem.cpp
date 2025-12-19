#include "MonitoringSystem.hpp"
#include <chrono>
#include <iostream>

MonitoringSystem::MonitoringSystem() = default;

MonitoringSystem::MonitoringSystem(const MonitoringSystem& other)
    : m_rooms(other.m_rooms)
    , m_user(other.m_user)
    , m_logger(other.m_logger)
{
}

void MonitoringSystem::SetUser(const std::shared_ptr<User>& user)
{
    m_user = user;
}

void MonitoringSystem::AddRoom(const RoomPtr& room)
{
    m_rooms.push_back(room);
}

void MonitoringSystem::PollSensors()
{
    using clock = std::chrono::system_clock;
    for (const auto& room : m_rooms)
    {
        for (std::size_t i = 0; i < room->GetSensorCount(); ++i)
        {
            try
            {
                auto sensor = (*room)[i]; // тут может вылететь std::out_of_range
                float value = sensor->ReadValue();
                auto measurement = Measurement(sensor->GetId(), value, clock::now());

                m_logger += "Measurement: " + sensor->GetId();
                std::cout << measurement << "\n";

                // Если датчик - температура, проверим аномалию.
                auto tempPtr = std::dynamic_pointer_cast<TemperatureSensor>(sensor);
                if (tempPtr && tempPtr->IsAnomalous())
                {
                    Alert alert(
                        "A-" + sensor->GetId(),
                        sensor->GetId(),
                        "Temperature is out of range",
                        Severity::Critical
                    );

                    m_logger.Log("ALERT for sensor " + sensor->GetId());
                    if (m_user)
                    {
                        m_user->ReceiveAlert(alert);
                    }
                    alert.SendSoundNotification();
                }
            }
            catch (const std::exception& ex)
            {
                // Демонстрация обработки исключений: перехватываем любые std::exception
                // и логируем их.
                m_logger.Log(std::string("Ошибка при опросе датчика в комнате '") +
                             room->GetName() + "': " + ex.what());
            }
        }
    }
}

