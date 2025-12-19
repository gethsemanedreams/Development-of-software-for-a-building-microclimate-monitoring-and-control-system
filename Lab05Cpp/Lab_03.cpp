#include <iostream>
#include <memory>
#include "MonitoringSystem.hpp"
#include "TemperatureSensor.hpp"
#include "Room.hpp"
#include "User.hpp"

/// Точка входа C++-проекта для ЛР-5.
/// Здесь мы:
///  * создаём систему мониторинга;
///  * демонстрируем использование std::shared_ptr / std::unique_ptr;
///  * оборачиваем критические участки в try/catch;
///  * показываем работу статических полей/методов Logger.
int main()
{
    try
    {
        MonitoringSystem system;

        auto user = std::make_shared<User>("U1", "Admin", "admin@example.com");
        system.SetUser(user);

        auto room = std::make_shared<Room>("Server room");

        // Создаём датчик температуры. Если min >= max – вылетит исключение,
        // которое мы отловим в внешнем try/catch.
        auto tempSensor = std::make_shared<TemperatureSensor>("T1", "CPU sensor", 18.0f, 27.0f);
        tempSensor->UpdateValue(39.3f); // Заведомо аномальное значение.

        room->AddSensor(tempSensor);
        system.AddRoom(room);

        system.PollSensors();

        // В конце выводим лог и статистику по количеству сообщений.
        system.GetLogger().DumpToConsole();
        std::cout << "Total log messages: " << Logger::GetTotalMessages() << "\n";
    }
    catch (const std::exception& ex)
    {
        // Глобальная точка обработки исключений.
        std::cerr << "Fatal error: " << ex.what() << std::endl;
        return 1;
    }

    std::cout << "Program finished successfully.\n";
    return 0;
}

