// Класс Measurement описывает одно измерение.
// Для демонстрации ЛР-5 добавляем конструктор копирования (через другой объект)
// и аккуратный ToString().
using System;

namespace Lab04Monitoring
{
    public class Measurement
    {
        public string SensorId { get; }
        public float Value { get; }
        public DateTime Timestamp { get; }

        public Measurement(string sensorId, float value, DateTime timestamp)
        {
            SensorId = sensorId;
            Value = value;
            Timestamp = timestamp;
        }

        // "Конструктор копирования" по образцу C++.
        public Measurement(Measurement other)
            : this(other.SensorId, other.Value, other.Timestamp)
        {
        }

        public override string ToString()
        {
            return $"Measurement(Sensor={SensorId}, Value={Value:F2}, Time={Timestamp:O})";
        }
    }
}
