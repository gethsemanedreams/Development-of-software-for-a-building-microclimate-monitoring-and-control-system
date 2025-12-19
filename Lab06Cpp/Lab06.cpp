#include <iostream>
#include <memory>
#include "Logger.hpp"
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
