// Класс MonitoringSystem управляет набором помещений и их датчиками.
using System.Collections.Generic;

namespace Lab04Monitoring
{
    public class MonitoringSystem
    {
        // Список всех помещений, входящих в систему мониторинга.
        private readonly List<Room> _rooms = new List<Room>();

        // Зарегистрировать новое помещение.
        public void AddRoom(Room room)
        {
            _rooms.Add(room);
        }

        // Опросить все датчики во всех помещениях.
        public void PollSensors()
        {
            Logger.Instance.Log("=== Start polling ===");

            foreach (var room in _rooms)
            {
                room.CheckAllSensors();
            }

            Logger.Instance.Log("=== End polling ===");
        }
    }
}
