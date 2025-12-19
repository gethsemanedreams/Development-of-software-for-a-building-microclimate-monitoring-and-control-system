using System;

namespace Lab06Monitoring
{
    /// <summary>
    /// Производный класс пользователя.
    ///
    /// ЛР-6:
    ///  * наследуемся от абстрактного класса UserBase;
    ///  * реализуем дополнительный интерфейс IContactInfo (множественное наследование);
    ///  * переопределяем виртуальный метод ReceiveAlert с вызовом base-реализации.
    /// </summary>
    public class AdminUser : UserBase, IContactInfo
    {
        public int Priority { get; }

        public AdminUser(string id, string name, string email, int priority)
            : base(id, name, email)
        {
            Priority = priority;
            Console.WriteLine($"AdminUser created: {Name} (priority {Priority})");
        }

        public override void ReceiveAlert(Alert alert)
        {
            Console.Write("[ADMIN] ");
            base.ReceiveAlert(alert); // вызов базового метода
        }
    }
}
