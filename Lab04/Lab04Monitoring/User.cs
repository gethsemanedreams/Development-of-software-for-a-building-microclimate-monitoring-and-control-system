// Класс User описывает пользователя системы мониторинга.
using System;

namespace Lab04Monitoring
{
    public class User
    {
        private readonly string _id;
        private readonly string _name;

        // Контактная информация (например, e-mail).
        private string _contactInfo;

        public User(string id, string name, string contactInfo)
        {
            _id = id;
            _name = name;
            _contactInfo = contactInfo;
        }

        // Пользователь получает оповещение.
        public void ReceiveAlert(Alert alert)
        {
            Console.WriteLine($"User '{_name}' ({_contactInfo}) received alert:");
            alert.SendTextNotification();
        }

        // Просмотр накопленного отчёта (лога).
        public void ViewReport()
        {
            Console.WriteLine($"User '{_name}' is viewing log:");
            Logger.Instance.PrintLog();
        }

        // Обновление контактной информации.
        public void SetContactInfo(string newInfo)
        {
            _contactInfo = newInfo;
            Console.WriteLine($"Contact info for '{_name}' updated to: {_contactInfo}");
        }
    }
}
