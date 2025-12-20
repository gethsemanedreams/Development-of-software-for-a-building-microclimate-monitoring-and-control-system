using System;

namespace Lab06Monitoring
{
    /// <summary>
    /// Датчик температуры.
    ///
    /// ЛР-6:
    ///  * переопределяем виртуальные методы;
    ///  * в Calibrate() вызываем базовую реализацию;
    ///  * реализуем Clone() (поверхностное клонирование);
    ///  * объявляем метод TypeName() с той же сигнатурой, что и в базовом классе,
    ///    но без virtual.
    /// </summary>
    public class TemperatureSensor : Sensor
    {
        public float MinThreshold { get; }
        public float MaxThreshold { get; }

        private static readonly Random _rnd = new();

        public TemperatureSensor(string id, string name, float min, float max)
            : base(id, name, "°C")
        {
            if (min >= max)
                throw new ArgumentException("min must be < max", nameof(min));

            MinThreshold = min;
            MaxThreshold = max;
        }

        public override float ReadValue()
        {
            LastValue = (float)(_rnd.NextDouble() * (MaxThreshold - MinThreshold + 20) + (MinThreshold - 10));
            Console.WriteLine($"TemperatureSensor '{Name}' read: {LastValue:F2} {Unit}");
            return LastValue;
        }

        public override bool CheckStatus()
        {
            bool ok = LastValue >= MinThreshold && LastValue <= MaxThreshold;
            Console.WriteLine($"TemperatureSensor '{Name}' status: {(ok ? "OK" : "OUT OF RANGE")}");
            return ok;
        }

        public override void Calibrate()
        {
            Console.WriteLine($"TemperatureSensor '{Name}': custom calibration...");
            base.Calibrate(); // вызов базового метода
        }

        public override string Describe()
        {
            return $"TemperatureSensor[{Id}] '{Name}', range = {MinThreshold}..{MaxThreshold} {Unit}";
        }

        public new string TypeName()
        {
            // new скрывает базовую реализацию (не полиморфно)
            return "TemperatureSensor";
        }

        public override object Clone()
        {
            // Поверхностное клонирование: копируем простые поля.
            return new TemperatureSensor(Id, Name, MinThreshold, MaxThreshold)
            {
                LastValue = this.LastValue,
                Status = this.Status
            };
        }
    }
}
