// Класс Alert описывает одно оповещение для пользователя.
// Здесь мы используем enum Severity и свойства вместо публичных полей.
using System;

namespace Lab04Monitoring
{
    public class Alert
    {
        // Идентификатор оповещения.
        public string Id { get; }

        // Идентификатор датчика-источника.
        public string SensorId { get; }

        // Текст сообщения.
        public string Message { get; }

        // Уровень серьёзности.
        public Severity Severity { get; }

        // Конструктор обычный.
        public Alert(string id, string sensorId, string message, Severity severity)
        {
            Id = id;
            SensorId = sensorId;
            Message = message;
            Severity = severity;
        }

        // Текстовое оповещение в консоль.
        public void SendTextNotification()
        {
            Console.WriteLine($"[ALERT {Id}] ({Severity}) from sensor {SensorId}: {Message}");
        }

        // "Звуковое" оповещение для демонстрации.
        public void SendSoundNotification()
        {
            Console.WriteLine("[SOUND ALERT] *beep* " + Message);
        }

        // Переопределяем ToString, чтобы удобно использовать Alert в логах.
        public override string ToString()
        {
            return $"Alert(Id={Id}, Sensor={SensorId}, Severity={Severity}, Message=\"{Message}\")";
        }
    }
}
