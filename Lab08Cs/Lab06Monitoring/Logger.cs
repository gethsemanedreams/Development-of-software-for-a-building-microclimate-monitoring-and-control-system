using System;
using System.Collections.Generic;

namespace Lab06Monitoring
{
    /// <summary>
    /// Простой Singleton-логгер.
    /// </summary>
    public sealed class Logger
    {
        private readonly List<string> _entries = new();

        private Logger() {}

        public static Logger Instance { get; } = new Logger();

        public void Log(string message)
        {
            _entries.Add(message);
        }

        public void Print()
        {
            Console.WriteLine("---- LOG BEGIN ----");
            foreach (var e in _entries)
            {
                Console.WriteLine(e);
            }
            Console.WriteLine("---- LOG END ----");
        }
    }
}
