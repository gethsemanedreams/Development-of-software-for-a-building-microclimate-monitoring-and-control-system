#include "Alert.hpp"

Alert::Alert(const std::string& id,
             const std::string& sensorId,
             const std::string& message,
             Severity severity)
    : m_id(id)
    , m_sensorId(sensorId)
    , m_message(message)
    , m_severity(severity)
{
}

Alert::Alert(const Alert& other)
    : m_id(other.m_id)
    , m_sensorId(other.m_sensorId)
    , m_message(other.m_message)
    , m_severity(other.m_severity)
{
    // Здесь копирование тривиальное, но явный конструктор копирования
    // нужен по условию ЛР-5.
}

void Alert::SendTextNotification() const
{
    std::cout << "[ALERT " << m_id << "] ("
              << SeverityToString(m_severity) << ") from sensor "
              << m_sensorId << ": " << m_message << std::endl;
}

void Alert::SendSoundNotification() const
{
    std::cout << "[SOUND ALERT] *beep* " << m_message << std::endl;
}

std::string Alert::SeverityToString(Severity severity)
{
    switch (severity)
    {
    case Severity::Info:     return "INFO";
    case Severity::Warning:  return "WARNING";
    case Severity::Critical: return "CRITICAL";
    default:                 return "UNKNOWN";
    }
}

std::ostream& operator<<(std::ostream& os, const Alert& a)
{
    // Перегрузка оператора вывода << (friend-функция).
    os << "Alert{" << a.m_id << ", sensor=" << a.m_sensorId
       << ", severity=" << Alert::SeverityToString(a.m_severity)
       << ", message=\"" << a.m_message << "\"}";
    return os;
}

