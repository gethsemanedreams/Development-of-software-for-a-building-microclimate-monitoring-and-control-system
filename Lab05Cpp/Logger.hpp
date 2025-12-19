#pragma once
#include <string>
#include <vector>
#include <iostream>

/// \brief Простой логгер.
/// В ЛР-5 здесь демонстрируем:
///  * статическое поле и статический метод (TotalMessages / GetTotalMessages);
///  * перегрузку оператора += для добавления строки в лог;
///  * использование std::string и std::vector<std::string>.
class Logger
{
private:
    std::vector<std::string> m_lines; ///< Собственно строки лога.

    /// \brief Статическое поле: общее количество записанных сообщений.
    /// Показывает "глобальную" статистику по всем объектам Logger.
    static std::size_t s_totalMessages;

public:
    Logger() = default;

    /// Конструктор копирования (по заданию ЛР-5).
    Logger(const Logger& other);

    /// \brief Добавить строку в лог обычным методом.
    void Log(const std::string& line);

    /// \brief Перегрузка оператора += как более "краткая" форма добавления.
    Logger& operator+=(const std::string& line);

    /// \brief Вывести содержимое лога на стандартный вывод.
    void DumpToConsole() const;

    /// \brief Статический метод для получения значения счётчика сообщений.
    /// Это пример "разумного использования" static-метода.
    static std::size_t GetTotalMessages();
};

