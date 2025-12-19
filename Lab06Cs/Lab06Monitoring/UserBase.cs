using System;

namespace Lab06Monitoring
{
    /// <summary>
    /// Абстрактный базовый класс пользователя.
    ///
    /// ЛР-6 (C#):
    ///  * абстрактный класс;
    ///  * реализует интерфейс IAlertSink;
    ///  * демонстрирует protected-свойства.
    /// </summary>
    public abstract class UserBase : IAlertSink
    {
        public string Id { get; }
        public string Name { get; protected set; }
        public string Email { get; protected set; }

        protected UserBase(string id, string name, string email)
        {
            Id = id;
            Name = name;
            Email = email;
        }

        public virtual void ReceiveAlert(Alert alert)
        {
            Console.WriteLine($"User '{Name}' received alert:");
            alert.SendTextNotification();
        }
    }
}
