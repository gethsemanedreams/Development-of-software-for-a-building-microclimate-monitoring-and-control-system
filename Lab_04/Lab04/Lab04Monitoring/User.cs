// Пользователь системы мониторинга.
using System;

namespace Lab04Monitoring
{
    public class User
    {
        public string Id { get; }
        public string Name { get; }
        public string Email { get; }

        public User(string id, string name, string email)
        {
            Id = id;
            Name = name;
            Email = email;
        }

        public void ReceiveAlert(Alert alert)
        {
            Console.WriteLine($"User '{Name}' ({Email}) received alert:");
            Console.WriteLine("  " + alert);
        }
    }
}
