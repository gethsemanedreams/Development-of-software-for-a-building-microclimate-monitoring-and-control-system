#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
#include <type_traits>
#include "Sensor.hpp"

/// \brief Шаблонный класс, управляющий группой датчиков.
///
/// Параметр шаблона TSensor должен быть наследником абстрактного класса Sensor.
/// В классе есть как обычные методы (Add, PrintAll), так и шаблонный метод FindByPredicate.
template <typename TSensor>
class SensorGroup
{
    static_assert(std::is_base_of<Sensor, TSensor>::value,
                  "TSensor must be derived from Sensor");

public:
    using Ptr = std::shared_ptr<TSensor>;

private:
    std::vector<Ptr> m_sensors; // контейнер STL с объектами-потомками Sensor

public:
    /// \brief Добавить датчик в группу.
    void Add(const Ptr& sensor)
    {
        m_sensors.push_back(sensor);
    }

    /// \brief Отсортировать датчики по идентификатору.
    void SortById()
    {
        std::sort(m_sensors.begin(), m_sensors.end(),
                  [](const Ptr& a, const Ptr& b)
                  {
                      return a->GetId() < b->GetId();
                  });
    }

    /// \brief Нешаблонный метод: печатает краткую информацию по всем датчикам.
    void PrintAll() const
    {
        std::cout << "SensorGroup contains " << m_sensors.size() << " sensor(s):" << std::endl;
        for (const auto& s : m_sensors)
        {
            if (s)
                s->PrintWithHeader();
        }
    }

    /// \brief Шаблонный метод: ищет датчик по произвольному предикату.
    template <typename Predicate>
    Ptr FindByPredicate(Predicate predicate) const
    {
        auto it = std::find_if(m_sensors.begin(), m_sensors.end(),
                               [&](const Ptr& s)
                               {
                                   return s && predicate(*s);
                               });
        if (it != m_sensors.end())
            return *it;
        return nullptr;
    }
};
