// Класс Room описывает одну комнату с набором датчиков.
// Здесь используем коллекцию List<Sensor> и методы работы со строками.
using System;
using System.Collections.Generic;
using System.Linq;

namespace Lab04Monitoring
{
    public class Room
    {
        public string Name { get; }

        private readonly List<Sensor> _sensors = new();

        public Room(string name)
        {
            Name = name;
        }

        public void AddSensor(Sensor sensor)
        {
            _sensors.Add(sensor);
        }

        public IReadOnlyList<Sensor> Sensors => _sensors;

        // Поиск датчика по идентификатору – пример работы со строками и LINQ.
        public Sensor? FindSensorById(string id)
        {
            return _sensors.FirstOrDefault(s => s.Id.Contains(id, StringComparison.OrdinalIgnoreCase));
        }
    }
}
