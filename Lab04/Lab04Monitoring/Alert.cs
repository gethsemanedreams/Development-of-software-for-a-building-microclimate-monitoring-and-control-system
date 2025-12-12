// Класс Alert описывает одно оповещение для пользователя.
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
            Console.WriteLine($"[ALERT {Id}] ({SeverityToString(Severity)}) from sensor {SensorId}: {Message}");
        }

        // "Звуковое" оповещение (подаём сигнал Beep, если возможно).
        public void SendSoundNotification()
        {
            try
            {
                Console.Beep();
            }
            catch
            {
                // Beep может не поддерживаться (виртуалка, удалённая консоль).
            }
        }

        // Преобразование enum в строку.
        public static string SeverityToString(Severity severity)
        {
            return severity switch
            {
                Severity.Info => "INFO",
                Severity.Warning => "WARNING",
                Severity.Critical => "CRITICAL",
                _ => "UNKNOWN"
            };
        }
    }
}
