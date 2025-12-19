// Консольное приложение для демонстрации работы библиотеки Lab04Monitoring.
// Здесь мы:
//   * создаём систему мониторинга;
//   * демонстрируем try/catch и выброс исключения в TemperatureSensor;
//   * выводим статистику Logger.TotalMessages.
using System;
using Lab04Monitoring;

namespace MonitoringSystem.Cli
{
    internal class Program
    {
        static void Main(string[] args)
        {
            // На всякий случай глобальный try/catch вокруг всей программы.
            try
            {
                Run();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Fatal error: " + ex.Message);
            }
        }

        private static void Run()
        {
            // Сбрасываем счётчики логгера перед началом.
            Logger.ResetStatistics();

            var logger = Logger.Instance;
            var system = new Lab04Monitoring.MonitoringSystem();

            var user = new User("U1", "Admin", "admin@example.com");
            system.SetUser(user);

            var room = new Room("Server room");

            // Пробуем создать датчик с корректными порогами.
            TemperatureSensor tempSensor;
            try
            {
                tempSensor = new TemperatureSensor("T1", "CPU sensor", 18.0f, 27.0f);
            }
            catch (ArgumentException ex)
            {
                // Этот блок демонстрирует локальный try/catch и работу с throw из конструктора.
                Console.WriteLine("Ошибка при создании датчика: " + ex.Message);
                return;
            }

            // Устанавливаем заведомо аномальное значение, чтобы сработал Alert.
            tempSensor.UpdateValue(39.3f);

            room.AddSensor(tempSensor);
            system.AddRoom(room);

            system.PollSensors();

            logger.DumpToConsole();
            logger.SaveToFile();

            Console.WriteLine("Total log messages: " + Logger.TotalMessages);
            Console.WriteLine("Program finished successfully.");
        }
    }
}
