#include "Logger.hpp"

std::size_t Logger::s_totalMessages = 0;

Logger::Logger(const Logger& other)
    : m_lines(other.m_lines)
{
    // Копируем содержимое лога.
    // Статическое поле s_totalMessages копировать НЕ нужно,
    // оно общее для всех объектов.
}

void Logger::Log(const std::string& line)
{
    m_lines.push_back(line);
    ++s_totalMessages;
}

Logger& Logger::operator+=(const std::string& line)
{
    // Используем указатель this, чтобы показать "разумное использование"
    // оператора this и реализацию "флюентного" интерфейса:
    // logger += "one" += "two";
    this->Log(line);
    return *this; // Возвращаем *this, чтобы можно было писать цепочки вызовов.
}

void Logger::DumpToConsole() const
{
    std::cout << "===== LOG START =====\n";
    for (const auto& line : m_lines)
    {
        std::cout << line << "\n";
    }
    std::cout << "===== LOG END   =====\n";
}

std::size_t Logger::GetTotalMessages()
{
    return s_totalMessages;
}

