#pragma once
#include <string>
#include <vector>
#include <iostream>

/// \brief Простой Singleton-логгер.
///
/// ЛР-5: уже использовался для логирования.
/// ЛР-6: здесь демонстрируем запрет копирования для класса,
///       у которого раньше мог бы быть конструктор копирования по умолчанию.
class Logger
{
    std::vector<std::string> m_entries;

    Logger() = default;

public:
    static Logger& Instance()
    {
        static Logger instance;
        return instance;
    }

    // ЛР-6: запрещаем копирование и присваивание.
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void Log(const std::string& message)
    {
        m_entries.push_back(message);
    }

    void Print() const
    {
        std::cout << "---- LOG BEGIN ----\n";
        for (const auto& e : m_entries)
        {
            std::cout << e << "\n";
        }
        std::cout << "---- LOG END ----\n";
    }
};
