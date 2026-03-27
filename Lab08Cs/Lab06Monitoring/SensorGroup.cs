using System;
using System.Collections.Generic;
using System.Linq;

namespace Lab06Monitoring
{
    /// <summary>
    /// Обобщённый класс, который хранит датчики конкретного типа.
    /// Тип параметра TSensor должен наследовать абстрактный класс Sensor.
    /// Внутри используются контейнеры .NET (List&lt;TSensor&gt;) и LINQ-алгоритмы.
    /// </summary>
    public class SensorGroup<TSensor> where TSensor : Sensor
    {
        private readonly List<TSensor> _sensors = new();

        /// <summary>
        /// Нешаблонный метод: добавить датчик в группу.
        /// </summary>
        public void Add(TSensor sensor)
        {
            if (sensor == null) throw new ArgumentNullException(nameof(sensor));
            _sensors.Add(sensor);
        }

        /// <summary>
        /// Нешаблонный метод: сортировка датчиков по имени (аналог std::sort).
        /// </summary>
        public void SortByName()
        {
            _sensors.Sort((a, b) => string.Compare(a.Name, b.Name, StringComparison.Ordinal));
        }

        /// <summary>
        /// Нешаблонный метод: печать всех датчиков.
        /// </summary>
        public void PrintAll()
        {
            Console.WriteLine($"SensorGroup&lt;{typeof(TSensor).Name}&gt; contains {_sensors.Count} sensor(s):");
            foreach (var s in _sensors)
            {
                s.PrintWithHeader();
            }
        }

        /// <summary>
        /// Шаблонный метод: поиск первого датчика по произвольному предикату.
        /// Обратите внимание, что сам класс уже обобщён по TSensor, а метод дополнительно
        /// использует обобщённый делегат для предиката.
        /// </summary>
        public TSensor? FindByPredicate(Func<TSensor, bool> predicate)
        {
            if (predicate == null) throw new ArgumentNullException(nameof(predicate));
            return _sensors.FirstOrDefault(predicate);
        }
    }
}
