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
    }
}
