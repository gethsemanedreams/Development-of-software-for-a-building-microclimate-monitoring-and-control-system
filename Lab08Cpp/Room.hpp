#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Sensor.hpp"

/// \brief Помещение, в котором установлены датчики.
///
/// ЛР-6: здесь реализуем поверхностное и глубокое клонирование.
class Room
{
    std::string              m_name;
    std::vector<SensorPtr>   m_sensors;

public:
    explicit Room(const std::string& name)
        : m_name(name)
    {
    }

    // Конструктор копирования по умолчанию подходит для поверхностной копии.
    Room(const Room&) = default;

    const std::string& GetName() const { return m_name; }

    void AddSensor(const SensorPtr& sensor)
    {
        m_sensors.push_back(sensor);
    }

    void CheckAllSensors();

    /// \brief Поверхностное клонирование.
    ///
    /// Room копируется, но SensorPtr остаются теми же (делят владение Sensor).
    std::shared_ptr<Room> ShallowClone() const;

    /// \brief Глубокое клонирование.
    ///
    /// Датчики клонируются через виртуальный метод Sensor::Clone().
    std::shared_ptr<Room> DeepClone() const;
};

using RoomPtr = std::shared_ptr<Room>;
