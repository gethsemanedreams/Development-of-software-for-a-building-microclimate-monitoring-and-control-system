// Конкретный датчик — температурный.
using System;

namespace Lab04Monitoring
{
    public class TemperatureSensor : Sensor
    {
        // Общий генератор случайных чисел для имитации показаний.
        private static readonly Random _rnd = new Random();

        // Допустимый диапазон температур.
        private readonly float _thresholdMin;
        private readonly float _thresholdMax;

        // Конструктор принимает идентификатор датчика и допустимый диапазон.
        public TemperatureSensor(string id, float min, float max)
            : base(id, $"Temperature sensor {id}", "C")
        {
            _thresholdMin = min;
            _thresholdMax = max;
        }

        // Имитация измерения температуры.
        public override float ReadValue()
        {
            // Случайное значение в диапазоне [-10; 50) градусов.
            LastValue = (float)(_rnd.NextDouble() * 60.0 - 10.0);
            Status = "OK";

            Logger.Instance.Log($"[{Id}] measured {LastValue:F2} {Unit}");
            return LastValue;
        }

        // Проверка, выходит ли измерение за допустимый диапазон.
        public bool IsOutOfRange()
        {
            return LastValue < _thresholdMin || LastValue > _thresholdMax;
        }

        // Текстовое представление "нормально/критично".
        public string GetWarningLevel()
        {
            return IsOutOfRange() ? "CRITICAL" : "NORMAL";
        }
    }
}
