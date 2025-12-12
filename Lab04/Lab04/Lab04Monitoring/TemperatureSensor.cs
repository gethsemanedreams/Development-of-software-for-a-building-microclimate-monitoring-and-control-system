// Конкретный датчик температуры.
// Здесь демонстрируем:
//   * вызов конструктора базового класса из конструктора дочернего;
//   * инициализацию исключения (throw new ArgumentException),
//     если пороговые значения заданы неверно.
using System;

namespace Lab04Monitoring
{
    public class TemperatureSensor : Sensor
    {
        public float MinThreshold { get; }
        public float MaxThreshold { get; }

        public TemperatureSensor(string id, string name, float minThreshold, float maxThreshold)
            : base(id, name, "°C") // Вызов конструктора базового класса Sensor.
        {
            if (minThreshold >= maxThreshold)
            {
                // Инициализация и выброс исключения – пример throw.
                throw new ArgumentException(
                    "Минимальный порог температуры должен быть меньше максимального.",
                    nameof(minThreshold));
            }

            MinThreshold = minThreshold;
            MaxThreshold = maxThreshold;
        }

        public override float ReadValue()
        {
            // В лабораторной используем уже сохранённое значение.
            return LastValue;
        }

        public void UpdateValue(float value)
        {
            LastValue = value;
        }

        public bool IsAnomalous()
        {
            return LastValue < MinThreshold || LastValue > MaxThreshold;
        }
    }
}
