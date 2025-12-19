using System;

namespace Lab06Monitoring
{
    /// <summary>
    /// Класс Alert описывает одно оповещение.
    /// </summary>
    public class Alert
    {
        public string Id { get; }
        public string SensorId { get; }
        public string Message { get; }
        public Severity Severity { get; }

        public Alert(string id, string sensorId, string message, Severity severity)
        {
            Id = id;
            SensorId = sensorId;
            Message = message;
            Severity = severity;

            Console.WriteLine($"Alert created: {message}");
        }

        public void SendTextNotification()
        {
            Console.WriteLine($"[ALERT {Id}] ({Severity}) from sensor {SensorId}: {Message}");
        }
    }
}
