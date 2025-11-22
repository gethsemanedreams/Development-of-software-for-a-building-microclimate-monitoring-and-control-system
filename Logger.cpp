#include "Logger.hpp"
#include <iostream>
#include <fstream>

// Реализация Singleton
Logger& Logger::GetInstance()
{
    static Logger instance;
    return instance;
}

void Logger::Log(const std::string& message)
{
    m_log.push_back(message);
}

void Logger::PrintLog() const
{
    std::cout << "---- LOG BEGIN ----\n";
    for (const auto& entry : m_log)
    {
        std::cout << entry << std::endl;
    }
    std::cout << "---- LOG END ----\n";
}

void Logger::SaveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Error: cannot open log file!\n";
        return;
    }

    for (const auto& entry : m_log)
    {
        file << entry << "\n";
    }

    file.close();
}