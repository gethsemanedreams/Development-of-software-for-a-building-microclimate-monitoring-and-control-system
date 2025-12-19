using System;

namespace Lab06Monitoring
{
    /// <summary>
    /// Датчик влажности.
    ///
    /// ЛР-6:
    ///  * второй пример наследования;
    ///  * переопределяем виртуальные методы;
    ///  * в Calibrate() НЕ вызываем базовую реализацию.
    /// </summary>
    public class HumiditySensor : Sensor
    {
        public float MinThreshold { get; }
        public float MaxThreshold { get; }

        private static readonly Random _rnd = new();

        public HumiditySensor(string id, string name, float min, float max)
            : base(id, name, "%")
        {
            if (min >= max)
                throw new ArgumentException("min must be < max", nameof(min));

            MinThreshold = min;
            MaxThreshold = max;
        }

        public override float ReadValue()
        {
            LastValue = (float)(_rnd.NextDouble() * (MaxThreshold - MinThreshold + 40) + (MinThreshold - 20));
            Console.WriteLine($"HumiditySensor '{Name}' read: {LastValue:F2} {Unit}");
            return LastValue;
        }

        public override bool CheckStatus()
        {
            bool ok = LastValue >= MinThreshold && LastValue <= MaxThreshold;
            Console.WriteLine($"HumiditySensor '{Name}' status: {(ok ? "OK" : "OUT OF RANGE")}");
            return ok;
        }

        public override void Calibrate()
        {
            Console.WriteLine($"HumiditySensor '{Name}': fast calibration without base call");
        }

        public override string Describe()
        {
            return $"HumiditySensor[{Id}] '{Name}', range = {MinThreshold}..{MaxThreshold} {Unit}";
        }

        public override object Clone()
        {
            return new HumiditySensor(Id, Name, MinThreshold, MaxThreshold)
            {
                LastValue = this.LastValue,
                Status = this.Status
            };
        }
    }
}
