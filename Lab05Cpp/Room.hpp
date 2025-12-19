#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Sensor.hpp"
#include "TemperatureSensor.hpp"

/// \brief Класс Room описывает одну комнату с набором датчиков.
///
/// В ЛР-5:
///  * используем std::shared_ptr для хранения датчиков;
///  * показываем работу со строками (поиск датчика по id / имени);
///  * перегружаем оператор << как friend.
class Room
{
private:
    std::string m_name;
    std::vector<SensorPtr> m_sensors;

public:
    explicit Room(const std::string& name);
    Room(const Room& other);

    const std::string& GetName() const { return m_name; }

    void AddSensor(const SensorPtr& sensor);

    /// Поиск датчика по идентификатору (пример использования std::string::find).
    SensorPtr FindSensorById(const std::string& id) const;

    /// Доступ к датчику по индексу (оператор []).
    SensorPtr operator[](std::size_t index) const;

    std::size_t GetSensorCount() const { return m_sensors.size(); }

    friend std::ostream& operator<<(std::ostream& os, const Room& room);
};

using RoomPtr = std::shared_ptr<Room>;

