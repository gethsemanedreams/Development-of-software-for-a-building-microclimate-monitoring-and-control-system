using System;
using System.Collections.Generic;
using System.Globalization;

namespace Lab04Monitoring
{
    // Класс Room описывает помещение, в котором установлены датчики.
    public class Room
    {
        // Имя комнаты.
        public string Name { get; }

        // Список датчиков в комнате.
        private readonly List<Sensor> _sensors = new();

        public Room(string name)
        {
            Name = name;
        }

        // Добавление датчика.
        public void AddSensor(Sensor sensor)
        {
            _sensors.Add(sensor);
        }

        // Опрос всех датчиков и вывод результатов.
        public void CheckAllSensors()
        {
            Logger.Instance.Log($"Checking sensors in room '{Name}'");

            foreach (var s in _sensors)
            {
                var value = s.ReadValue();
                var ok = s.CheckStatus();

                Console.WriteLine(
                    $"Room '{Name}': {s.Name} = {value.ToString("F2", CultureInfo.InvariantCulture)} " +
                    $"{s.Unit}, status={s.Status}, ok={ok}"
                );
            }
        }
    }
}
