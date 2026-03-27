using System;
using System.Collections.Generic;

namespace Lab06Monitoring
{
    /// <summary>
    /// Система мониторинга, которая хранит набор помещений.
    /// </summary>
    public class MonitoringSystem
    {
        private readonly List<Room> _rooms = new();

        public void AddRoom(Room room)
        {
            _rooms.Add(room);
        }

        public void PollSensors()
        {
            Logger.Instance.Log("MonitoringSystem: start polling all rooms");
            Console.WriteLine("MonitoringSystem: polling all rooms...");

            foreach (var room in _rooms)
            {
                Logger.Instance.Log("Polling room: " + room.Name);
                room.CheckAllSensors();
            }

            Logger.Instance.Log("MonitoringSystem: finish polling all rooms");
        }


        /// <summary>
        /// Собирает в один список все датчики во всех комнатах.
        /// В ЛР‑8 это используется как контейнер List&lt;Sensor&gt; для демонстрации
        /// алгоритмов сортировки и поиска.
        /// </summary>
        public List<Sensor> GetAllSensorsSnapshot()
        {
            var result = new List<Sensor>();
            foreach (var room in _rooms)
            {
                result.AddRange(room.GetSensorsReadonly());
            }

            return result;
        }
    }
}
