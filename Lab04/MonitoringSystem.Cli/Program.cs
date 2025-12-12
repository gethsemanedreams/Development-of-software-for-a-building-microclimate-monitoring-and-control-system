// Точка входа консольного приложения на C#, которое демонстрирует работу библиотеки Lab04Monitoring.
using System;
using System.Globalization;
using Lab04Monitoring;

namespace Lab04Monitoring.Cli
{
    internal class Program
    {
        static void Main(string[] args)
        {
            // Получаем экземпляр логгера (синглтон).
            var logger = Logger.Instance;

            // Создаём саму систему мониторинга.
            var system = new MonitoringSystem();

            // Создаём помещение "Server room".
            var room1 = new Room("Server room");

            // Добавляем в него один температурный датчик с диапазоном 18..27 градусов.
            var tempSensor = new TemperatureSensor("T1", 18.0f, 27.0f);
            room1.AddSensor(tempSensor);

            // Регистрируем помещение в системе.
            system.AddRoom(room1);

            // Опрос всех датчиков во всех помещениях (в нашем случае — один датчик в одной комнате).
            system.PollSensors();

            // Создаём объект Measurement на основании последнего измерения датчика.
            var measurement = new Measurement(
                tempSensor.Id,
                tempSensor.LastValue,
                DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss", CultureInfo.InvariantCulture)
            );

            Console.WriteLine("Measurement: " + measurement);

            // Если значение вне диапазона 18..27 — формируем оповещение и отправляем пользователю.
            if (measurement.IsAnomalous(18.0f, 27.0f))
            {
                var alert = new Alert(
                    "A1",
                    tempSensor.GetId(),
                    "Temperature is out of range",
                    Severity.Critical
                );

                var user = new User("U1", "Admin", "admin@example.com");
                user.ReceiveAlert(alert);
                alert.SendSoundNotification();
            }

            // Сохраняем лог в файл и завершаем работу.
            logger.SaveToFile();
            Console.WriteLine("Program finished successfully.");
        }
    }
}
