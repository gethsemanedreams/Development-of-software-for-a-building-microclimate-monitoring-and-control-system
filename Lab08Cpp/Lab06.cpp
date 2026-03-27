#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <numeric>
#include <variant>
#include "Logger.hpp"
#include "SensorGroup.hpp"
#include "MathUtils.hpp"
#include "MonitoringSystem.hpp"
#include "TemperatureSensor.hpp"
#include "HumiditySensor.hpp"
#include "User.hpp"
#include "Alert.hpp"

/// \brief Главная функция демонстрации возможностей ЛР-6 по C++.
///
/// Здесь мы показываем:
///  * наследование (TemperatureSensor, HumiditySensor, AdminUser);
///  * protected-поля (доступ из производных классов);
///  * переопределение виртуальных методов (Calibrate, Describe, CheckStatus);
///  * вызов виртуального метода через невиртуальный (PrintWithHeader -> Describe);
///  * разницу между виртуальной и невиртуальной функцией (Describe vs TypeName);
///  * виртуальный деструктор Sensor (delete через указатель на базу);
///  * поверхностное и глубокое клонирование Room;
///  * перегрузку оператора присваивания от базового класса (TemperatureSensor = Sensor&);
int main()
{
    try
    {
        // Создаём два датчика.
        auto temp = std::make_shared<TemperatureSensor>("T1", "Server inlet", 18.0f, 25.0f);
        auto hum  = std::make_shared<HumiditySensor>("H1", "Server humidity", 30.0f, 60.0f);

        // Демонстрация виртуальной функции Describe и невиртуальной TypeName.
        Sensor* basePtr = temp.get();
        std::cout << "Describe via base pointer: " << basePtr->Describe() << std::endl;
        std::cout << "TypeName via base pointer: " << basePtr->TypeName() << std::endl;
        std::cout << "TypeName via derived object: " << temp->TypeName() << std::endl;

        // Вызов виртуальной функции через невиртуальную обёртку.
        basePtr->PrintWithHeader();

        // Переопределённые методы Calibrate:
        temp->Calibrate(); // с вызовом Sensor::Calibrate()
        hum->Calibrate();  // без вызова базовой реализации

        // Создаём комнату и добавляем датчики.
        auto room = std::make_shared<Room>("Server room");
        room->AddSensor(temp);
        room->AddSensor(hum);

        // Поверхностное и глубокое клонирование.
        auto shallow = room->ShallowClone();
        auto deep    = room->DeepClone();

        // Система мониторинга.
        MonitoringSystem system;
        system.AddRoom(room);
        system.AddRoom(deep);

        // Опрос всех датчиков во всех помещениях.
        system.PollSensors();
        // ==== ЛР-8: демонстрация контейнеров и алгоритмов STL ====
        using SensorPtr = std::shared_ptr<Sensor>;

        // Вектор с указателями на базовый тип, внутри лежат объекты разных классов (TemperatureSensor, HumiditySensor).
        std::vector<SensorPtr> sensorList = { temp, hum };

        // Сортируем датчики по идентификатору (std::sort).
        std::sort(sensorList.begin(), sensorList.end(),
                  [](const SensorPtr& a, const SensorPtr& b)
                  {
                      return a->GetId() < b->GetId();
                  });

        // Ищем датчик по Id с помощью std::find_if.
        auto found = std::find_if(sensorList.begin(), sensorList.end(),
                                  [](const SensorPtr& s)
                                  {
                                      return s->GetId() == "T1";
                                  });

        if (found != sensorList.end())
        {
            std::cout << "std::find_if: found sensor with id T1 -> "
                      << (*found)->Describe() << std::endl;
        }

        // Проверяем, есть ли хотя бы один датчик с ошибочным статусом (std::any_of).
        bool anyError = std::any_of(sensorList.begin(), sensorList.end(),
                                    [](const SensorPtr& s)
                                    {
                                        return !s->CheckStatus();
                                    });
        std::cout << "std::any_of: any sensor in error state? "
                  << (anyError ? "yes" : "no") << std::endl;

        // Покажем пример использования std::map для быстрого поиска датчика по Id.
        std::map<std::string, SensorPtr> sensorIndex;
        for (const auto& s : sensorList)
        {
            sensorIndex[s->GetId()] = s;
        }

        auto it = sensorIndex.find("H1");
        if (it != sensorIndex.end())
        {
            std::cout << "std::map::find: found sensor H1 -> "
                      << it->second->Describe() << std::endl;
        }

        // Пример использования std::variant: значение измерения либо число, либо строка с ошибкой.

        // Удалим из копии вектора все датчики с ошибочным статусом при помощи std::remove_if.
        std::vector<SensorPtr> okSensors = sensorList;
        auto newEnd = std::remove_if(okSensors.begin(), okSensors.end(),
                                     [](const SensorPtr& s)
                                     {
                                         return !s->CheckStatus();
                                     });
        okSensors.erase(newEnd, okSensors.end());
        std::cout << "After std::remove_if there are " << okSensors.size()
                  << " OK sensor(s) in the copy container." << std::endl;

        std::variant<float, std::string> measurementValue = 39.3f;
        if (anyError)
        {
            measurementValue = std::string("no valid data");
        }

        std::visit(
            [](const auto& v)
            {
                std::cout << "std::variant holds: " << v << std::endl;
            },
            measurementValue);

        // Используем шаблонную функцию ComputeAverage для вычисления среднего значения.
        std::vector<float> values;
        values.reserve(sensorList.size());
        for (const auto& s : sensorList)
        {
            values.push_back(s->GetLastValue());
        }

        try
        {
            float avg = ComputeAverage(values);
            std::cout << "Average sensor value (ComputeAverage<T>): " << avg << std::endl;
        }
        catch (const std::exception& ex)
        {
            std::cout << "ComputeAverage error: " << ex.what() << std::endl;
        }

        // Демонстрация шаблонного класса SensorGroup.
        SensorGroup<TemperatureSensor> tempGroup;
        tempGroup.Add(temp);
        tempGroup.SortById();
        tempGroup.PrintAll();

        auto highTemp = tempGroup.FindByPredicate(
            [](const TemperatureSensor& s)
            {
                return s.GetLastValue() > 0.0f; // предикат для шаблонного метода
            });

        if (highTemp)
        {
            std::cout << "SensorGroup::FindByPredicate found: "
                      << highTemp->Describe() << std::endl;
        }



        // Клонирование отдельного датчика через виртуальный метод Clone().
        std::unique_ptr<Sensor> cloned(temp->Clone());
        std::cout << "Cloned sensor description: " << cloned->Describe() << std::endl;

        // Перегрузка оператора присваивания от базового класса.
        TemperatureSensor another("T2", "Spare sensor", 10.0f, 30.0f);
        another = *basePtr; // присваиваем состояние базового Sensor объекту производного класса
        std::cout << "After assignment, another sensor description: "
                  << another.Describe() << std::endl;

        // Виртуальный деструктор: удаляем объект производного класса через указатель на базу.
        Sensor* dynamicSensor = new TemperatureSensor("T3", "Dynamic sensor", 15.0f, 28.0f);
        delete dynamicSensor; // будет вызван ~TemperatureSensor, а затем ~Sensor

        // Демонстрация работы Alert и AdminUser.
        Alert alert("A1", "T1", "Temperature out of range", Severity::Critical);
        AdminUser admin("U1", "Admin", "admin@example.com", 10);
        admin.ReceiveAlert(alert);

        // Печать лога.
        Logger::Instance().Print();

        std::cout << "\nProgram finished successfully (C++ Lab06)." << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cout << "Exception: " << ex.what() << std::endl;
    }
}
