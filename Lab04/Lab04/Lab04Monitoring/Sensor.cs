// Абстрактный базовый класс для любых датчиков.
// Здесь:
//   * используем свойства вместо публичных полей;
//   * демонстрируем разумное использование this в методе SetStatus.
using System;

namespace Lab04Monitoring
{
    public abstract class Sensor
    {
        public string Id { get; }
        public string Name { get; }
        public string Unit { get; }

        // Последнее значение и статус датчика храним в свойствах.
        public float LastValue { get; protected set; }
        public string Status { get; private set; } = "OK";

        protected Sensor(string id, string name, string unit)
        {
            Id = id;
            Name = name;
            Unit = unit;
        }

        // Абстрактное чтение значения – каждый потомок реализует по‑своему.
        public abstract float ReadValue();

        public virtual bool CheckStatus() => Status == "OK";

        public virtual void Calibrate()
        {
            Logger.Instance.Log($"Sensor {Id} calibrated.");
        }

        // Метод использует this, возвращает сам объект.
        // Это позволяет писать цепочки вида: sensor.SetStatus("ERROR").Calibrate();
        public Sensor SetStatus(string status)
        {
            this.Status = status; // Явное использование this для наглядности.
            return this;
        }
    }
}
