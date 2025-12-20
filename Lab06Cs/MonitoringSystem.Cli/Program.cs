using System;
using Lab06Monitoring;

namespace Lab06Monitoring.Cli
{
    internal class Program
    {
        static void Main(string[] args)
        {
            try
            {
                RunDemo();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Fatal error: " + ex.Message);
            }
        }

        private static void RunDemo()
        {
            // Создаём датчики.
            var temp = new TemperatureSensor("T1", "Server inlet", 18, 25);
            var hum  = new HumiditySensor("H1", "Server humidity", 30, 60);

            // Виртуальная функция Describe и невиртуальная TypeName.
            Sensor baseRef = temp;
            Console.WriteLine("Describe via base: " + baseRef.Describe());
            Console.WriteLine("TypeName via base: " + baseRef.TypeName());
            Console.WriteLine("TypeName via derived: " + temp.TypeName());

            // Вызов виртуального метода через невиртуальный.
            baseRef.PrintWithHeader();

            // Переопределённые Calibrate: с и без вызова base.
            temp.Calibrate();
            hum.Calibrate();

            // Комната и клонирование.
            var room = new Room("Server room");
            room.AddSensor(temp);
            room.AddSensor(hum);

            var shallow = (Room)room.Clone();
            var deep    = room.DeepClone();

            // Система мониторинга.
            var system = new Lab06Monitoring.MonitoringSystem();
            system.AddRoom(room);
            system.AddRoom(deep);

            system.PollSensors();

            // Клонирование отдельного датчика.
            var clonedSensor = (Sensor)temp.Clone();
            Console.WriteLine("Cloned sensor description: " + clonedSensor.Describe());

            // Пользователи и интерфейсы.
            var admin = new AdminUser("U1", "Admin", "admin@example.com", 10);
            var alert = new Alert("A1", "T1", "Temperature out of range", Severity.Critical);
            admin.ReceiveAlert(alert);

            // Печать лога.
            Logger.Instance.Print();

            Console.WriteLine();
            Console.WriteLine("Program finished successfully (C# Lab06).");
        }
    }
}
