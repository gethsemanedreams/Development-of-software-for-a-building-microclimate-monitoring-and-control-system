using System;
using System.Collections.Generic;

namespace Lab06Monitoring
{
    /// <summary>
    /// Помещение, содержащее набор датчиков.
    ///
    /// ЛР-6:
    ///  * реализуем поверхностное и глубокое клонирование (через Clone датчиков);
    /// </summary>
    public class Room : ICloneable
    {
        private readonly List<Sensor> _sensors = new();

        public string Name { get; }

        public Room(string name)
        {
            Name = name;
        }

        public void AddSensor(Sensor sensor)
        {
            _sensors.Add(sensor);
        }

        public void CheckAllSensors()
        {
            Console.WriteLine($"Checking sensors in room '{Name}'...");
            foreach (var sensor in _sensors)
            {
                sensor.ReadValue();
                sensor.CheckStatus();
            }
        }

        /// <summary>
        /// Поверхностное клонирование комнаты (датчики те же).
        /// </summary>
        public object Clone()
        {
            var clone = new Room(Name);
            foreach (var s in _sensors)
                clone.AddSensor(s); // те же ссылки на датчики

            Console.WriteLine($"Room '{Name}' shallow-cloned.");
            return clone;
        }

        /// <summary>
        /// Глубокое клонирование комнаты (датчики клонируются).
        /// </summary>
        public Room DeepClone()
        {
            var clone = new Room(Name);
            foreach (var s in _sensors)
            {
                if (s.Clone() is Sensor sensorClone)
                    clone.AddSensor(sensorClone);
            }

            Console.WriteLine($"Room '{Name}' deep-cloned.");
            return clone;
        }


        /// <summary>
        /// Возвращает только чтение списка датчиков в комнате.
        /// Используется в ЛР‑8 для построения контейнера всех датчиков в системе.
        /// </summary>
        public IReadOnlyList<Sensor> GetSensorsReadonly()
        {
            return _sensors.AsReadOnly();
        }
    }
}
