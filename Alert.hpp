#pragma once
#include <string>
#include <iostream>

//
// Класс Alert описывает предупреждение,
// возникающее при превышении пороговых значений датчиков.
// Хранит информацию о типе, уровне и времени события.
//
class Alert
{
private:
    std::string m_id;         // Уникальный идентификатор предупреждения
    std::string m_sensorId;   // ID датчика, вызвавшего тревогу
    std::string m_message;    // Текст сообщения
    std::string m_severity;   // Уровень критичности (LOW / HIGH / CRITICAL)
    std::string m_timestamp;  // Время возникновения (строкой для простоты)

public:
    Alert(const std::string& id, const std::string& sensorId,
        const std::string& message, const std::string& severity,
        const std::string& timestamp);
    ~Alert();

    // Отправляет звуковое оповещение пользователю.
    void SendSoundNotification();

    // Отправляет текстовое уведомление.
    void SendTextNotification() const;

    // Подтверждение получения уведомления.
    void Acknowledge();
};
