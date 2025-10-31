#include "Alert.h"

Alert::Alert(const std::string& id, const std::string& sensorId,
    const std::string& message, const std::string& severity,
    const std::string& timestamp)
    : m_id(id), m_sensorId(sensorId), m_message(message),
    m_severity(severity), m_timestamp(timestamp)
{
    std::cout << "Alert created: " << m_message << std::endl;
}

Alert::~Alert()
{
    std::cout << "Alert destroyed: " << m_id << std::endl;
}

void Alert::SendSoundNotification()
{
    std::cout << "[SOUND ALERT] Sensor " << m_sensorId
        << " triggered: " << m_message << std::endl;
}

void Alert::SendTextNotification() const
{
    std::cout << "[TEXT ALERT] " << m_message
        << " | Level: " << m_severity << std::endl;
}

void Alert::Acknowledge()
{
    std::cout << "Alert " << m_id << " acknowledged by user." << std::endl;
}