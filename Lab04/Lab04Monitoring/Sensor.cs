using System;

namespace Lab04Monitoring
{
    // Абстрактный базовый класс для любых датчиков.
    public abstract class Sensor
    {
        // Используем СВОЙСТВА, а не "сырые" поля.
        // Свойства публичные (get), чтобы их можно было читать из Room и других классов,
        // а устанавливать значения можно только из самого датчика или наследников.

        // Идентификатор датчика (например, "T1").
        public string Id { get; }

        // Человекочитаемое имя датчика.
        public string Name { get; }

        // Единица измерения (например, "C").
        public string Unit { get; }

        // Последнее измеренное значение.
        public float LastValue { get; protected set; }

        // Статус датчика ("OK", "ERROR" и т.п.).
        public string Status { get; protected set; }

        // Базовый конструктор заполняет общие свойства.
        protected Sensor(string id, string name, string unit)
        {
            Id = id;
            Name = name;
            Unit = unit;
            LastValue = 0.0f;
            Status = "OK";
        }

        // Абстрактный метод: потомки обязаны реализовать чтение значения.
        public abstract float ReadValue();

        // Проверяем, всё ли в порядке с датчиком.
        public virtual bool CheckStatus()
        {
            return Status == "OK";
        }

        // "Калибровка" датчика — пока только запись в лог.
        public virtual void Calibrate()
        {
            Logger.Instance.Log($"Sensor {Id} calibrated.");
        }

        public string GetId() => Id;
        public string GetName() => Name;
        public string GetUnit() => Unit;
        public float GetLastValue() => LastValue;
        public string GetStatus() => Status;
    }
}
