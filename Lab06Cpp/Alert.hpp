#pragma once
#include <string>
#include <iostream>

/// \brief Уровень важности оповещения.
enum class Severity
{
    Info,
    Warning,
    Critical
};

/// \brief Класс Alert описывает одно оповещение.
///
/// ЛР-6 здесь напрямую не добавляет требований, но объект используется
/// при демонстрации работы системы.
class Alert
{
    std::string m_id;
    std::string m_sensorId;
    std::string m_message;
    Severity    m_severity{};

public:
    Alert(const std::string& id,
          const std::string& sensorId,
          const std::string& message,
          Severity severity)
        : m_id(id)
        , m_sensorId(sensorId)
        , m_message(message)
        , m_severity(severity)
    {
        std::cout << "Alert created: " << m_message << std::endl;
    }

    Alert(const Alert&) = default;

    ~Alert()
    {
        std::cout << "Alert destroyed: " << m_id << std::endl;
    }

    void SendTextNotification() const
    {
        std::cout << "[ALERT " << m_id << "] ("
                  << SeverityToString(m_severity) << ") from sensor "
                  << m_sensorId << ": " << m_message << std::endl;
    }

    static std::string SeverityToString(Severity severity)
    {
        switch (severity)
        {
        case Severity::Info:     return "INFO";
        case Severity::Warning:  return "WARNING";
        case Severity::Critical: return "CRITICAL";
        }
        return "UNKNOWN";
    }
};
