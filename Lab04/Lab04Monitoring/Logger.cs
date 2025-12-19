// Класс Logger — простой синглтон-логгер для записи событий работы системы мониторинга.
using System;
using System.Collections.Generic;
using System.IO;

namespace Lab04Monitoring
{
    public sealed class Logger
    {
        // Единственный экземпляр логгера (паттерн Singleton).
        private static readonly Logger _instance = new Logger();

        // Внутренний список строк с сообщениями журнала.
        private readonly List<string> _log = new List<string>();

        // Публичный доступ к экземпляру логгера.
        public static Logger Instance => _instance;

        // Закрытый конструктор запрещает создавать объект извне.
        private Logger() { }

        // Записать сообщение в лог с отметкой времени.
        public void Log(string message)
        {
            _log.Add($"{DateTime.Now:O} {message}");
        }

        // Вывести содержимое лога в консоль.
        public void PrintLog()
        {
            foreach (var line in _log)
            {
                Console.WriteLine(line);
            }
        }

        // Сохранить лог в текстовый файл.
        public void SaveToFile(string filename = "log.txt")
        {
            File.WriteAllLines(filename, _log);
        }
    }
}
