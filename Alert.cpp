#include "Alert.hpp"

// Конструктор
Alert::Alert(const std::string& id,
    const std::string& sensorId,
    const std::string& message,
    Severity severity)
    : m_id(id),
    m_sensorId(sensorId),
    m_message(message),
    m_severity(severity)
{
    std::cout << "Alert created: " << m_message << std::endl;
}

// Деструктор
Alert::~Alert()
{
    std::cout << "Alert destroyed: " << m_id << std::endl;
}

// Уведомление текстом
void Alert::SendTextNotification() const
{
    std::cout << "[TEXT ALERT] "
        << m_message
        << " | Level: "
        << SeverityToString(m_severity)
        << std::endl;
}

// Уведомление звуком
void Alert::SendSoundNotification() const
{
    std::cout << "[SOUND ALERT] *beep* "
        << m_message << std::endl;
}

// Преобразование enum → строка
std::string Alert::SeverityToString(Severity severity)
{
    switch (severity)
    {
    case Severity::INFO:     return "INFO";
    case Severity::WARNING:  return "WARNING";
    case Severity::CRITICAL: return "CRITICAL";
    }
    return "UNKNOWN";
}