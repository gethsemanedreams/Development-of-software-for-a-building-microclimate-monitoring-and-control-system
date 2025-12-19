// Класс Logger отвечает за сбор и сохранение диагностических сообщений.
// В этом классе демонстрируем:
//   * использование статического поля и статического метода (TotalMessages / ResetStatistics);
//   * использование коллекций и строк;
//   * работу оператора using (StreamWriter) для корректного освобождения ресурсов.
using System;
using System.Collections.Generic;
using System.IO;

namespace Lab04Monitoring
{
    public sealed class Logger
    {
        // Статическое поле: общее количество записанных сообщений во всех логгерах.
        // Это пример "глобальной" статистики.
        public static int TotalMessages { get; private set; }

        private readonly List<string> _lines = new();

        // Приватный конструктор и статическое свойство Instance превращают Logger
        // в синглтон – для простоты лабораторной.
        private static readonly Logger _instance = new Logger();

        public static Logger Instance => _instance;

        // Обычный метод записи сообщения в лог.
        public void Log(string message)
        {
            string line = $"[{DateTime.Now:HH:mm:ss}] {message}";
            _lines.Add(line);
            TotalMessages++;
        }

        // Демонстрация статического метода: сбросить глобальную статистику.
        public static void ResetStatistics()
        {
            TotalMessages = 0;
        }

        // Сохранение лога в файл. Здесь используется оператор using
        // для корректного закрытия StreamWriter.
        public void SaveToFile(string fileName = "log.txt")
        {
            using var writer = new StreamWriter(fileName);
            foreach (var line in _lines)
            {
                writer.WriteLine(line);
            }
        }

        // Печать лога в консоль для отладки.
        public void DumpToConsole()
        {
            Console.WriteLine("===== LOG START =====");
            foreach (var line in _lines)
            {
                Console.WriteLine(line);
            }
            Console.WriteLine("===== LOG END   =====");
        }
    }
}
