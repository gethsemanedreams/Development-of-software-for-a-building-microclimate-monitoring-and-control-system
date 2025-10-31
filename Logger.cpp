#include "Logger.h"

//
// Определение статического поля класса.
// Оно существует в единственном экземпляре для всех объектов Logger.
//
const std::string Logger::DEFAULT_NAME = "log.txt";

//
// Конструктор по умолчанию.
// Устанавливает имя файла равным значению по умолчанию.
//
Logger::Logger()
    : m_fileName(DEFAULT_NAME)
{
}

//
// Конструктор, позволяющий задать имя файла вручную.
//
Logger::Logger(const std::string& fileName)
    : m_fileName(fileName)
{
}

//
// Деструктор.
// Вызывается автоматически при уничтожении объекта.
// Закрывает файл, если он был открыт.
//
Logger::~Logger()
{
    Close();
}

//
// Метод Open()
// Открывает файл в режиме добавления (std::ios::app).
// Это позволяет не перезаписывать существующий журнал.
//
void Logger::Open()
{
    m_stream.open(m_fileName, std::ios::app);
}

//
// Метод Write()
// Записывает строку в файл, если файл открыт.
// Каждая запись завершается переводом строки.
//
void Logger::Write(const std::string& message)
{
    if (m_stream.is_open())
        m_stream << message << std::endl;
}

//
// Метод Close()
// Закрывает поток файла, если он открыт.
// Это освобождает ресурс и предотвращает утечки.
//
void Logger::Close()
{
    if (m_stream.is_open())
        m_stream.close();
}