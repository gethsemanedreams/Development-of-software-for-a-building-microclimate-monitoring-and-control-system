// Центральная система мониторинга.
// В этом классе показано:
//   * хранение комнат и пользователя;
//   * использование Logger;
//   * обработка исключений при опросе датчиков.
using System;
using System.Collections.Generic;

namespace Lab04Monitoring
{
    public class MonitoringSystem
    {
        private readonly List<Room> _rooms = new();
        private User? _user;

        public void SetUser(User user)
        {
            _user = user;
        }

        public void AddRoom(Room room)
        {
            _rooms.Add(room);
        }

        // Опрос всех датчиков с обработкой исключений.
        public void PollSensors()
        {
            foreach (var room in _rooms)
            {
                foreach (var sensor in room.Sensors)
                {
                    try
                    {
                        float value = sensor.ReadValue();
                        var measurement = new Measurement(sensor.Id, value, DateTime.Now);

                        Logger.Instance.Log($"Measurement from {sensor.Id} in room '{room.Name}' = {value:F2}");
                        Console.WriteLine(measurement);

                        if (sensor is TemperatureSensor temp && temp.IsAnomalous())
                        {
                            var alert = new Alert(
                                id: "A_" + sensor.Id,
                                sensorId: sensor.Id,
                                message: "Temperature is out of range",
                                severity: Severity.Critical);

                            Logger.Instance.Log($"ALERT for sensor {sensor.Id} in room '{room.Name}'");
                            _user?.ReceiveAlert(alert);
                            alert.SendSoundNotification();
                        }
                    }
                    catch (Exception ex)
                    {
                        // Демонстрация использования try/catch:
                        // здесь ловим любые ошибки, связанные с конкретным датчиком,
                        // и просто записываем их в лог, не падая всей программой.
                        Logger.Instance.Log($"Ошибка при опросе датчика {sensor.Id} в комнате '{room.Name}': {ex.Message}");
                    }
                }
            }
        }
    }
}
