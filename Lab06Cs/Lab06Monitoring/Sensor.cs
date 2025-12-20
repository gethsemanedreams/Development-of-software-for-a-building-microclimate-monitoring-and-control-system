using System;

namespace Lab06Monitoring
{
    /// <summary>
    /// Абстрактный базовый класс для любых датчиков.
    ///
    /// ЛР-6:
    ///  * демонстрируем protected-свойства (protected set);
    ///  * вводим виртуальные методы (ReadValue, Describe, Clone);
    ///  * демонстрируем вызов виртуального метода через невиртуальный (PrintWithHeader);
    ///  * показываем разницу между виртуальной и невиртуальной функцией (Describe vs TypeName);
    ///  * реализуем поверхностное/глубокое клонирование в связке с Room.
    /// </summary>
    public abstract class Sensor : ICloneable
    {
        public string Id { get; }
        public string Name { get; }
        public string Unit { get; }

        public float LastValue { get; protected set; }
        public string Status { get; protected set; } = "OK";

        protected Sensor(string id, string name, string unit)
        {
            Id = id;
            Name = name;
            Unit = unit;
        }

        /// <summary>
        /// Виртуальное чтение значения.
        /// </summary>
        public abstract float ReadValue();

        /// <summary>
        /// Виртуальная проверка состояния.
        /// </summary>
        public virtual bool CheckStatus()
        {
            Console.WriteLine($"Checking status of sensor '{Name}': {Status}");
            return Status == "OK";
        }

        /// <summary>
        /// Виртуальная калибровка.
        /// </summary>
        public virtual void Calibrate()
        {
            Logger.Instance.Log($"Base calibration for sensor {Id}");
        }

        /// <summary>
        /// Виртуальное описание датчика.
        /// </summary>
        public virtual string Describe()
        {
            return $"Sensor[{Id}] '{Name}' ({Unit})";
        }

        /// <summary>
        /// Невиртуальный метод, который вызывает виртуальный Describe().
        /// </summary>
        public void PrintWithHeader()
        {
            Console.WriteLine("[Sensor info] " + Describe());
        }

        /// <summary>
        /// Невиртуальный метод. В производных классах объявим метод с тем же
        /// именем и сигнатурой, чтобы показать разницу при вызове через базовый
        /// и производный тип.
        /// </summary>
        public string TypeName()
        {
            return "BaseSensor";
        }

        /// <summary>
        /// Поддержка поверхностного клонирования через ICloneable.
        /// Конкретные классы переопределяют Clone(), возвращая свой тип.
        /// </summary>
        public abstract object Clone();

        /// <summary>
        /// Метод, демонстрирующий использование this (возвращаем сам объект).
        /// </summary>
        public Sensor SetStatus(string status)
        {
            this.Status = status; // явное использование this
            return this;
        }
    }
}
