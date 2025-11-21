#pragma once
#include <string>
#include <iostream>

// Перечисление уровня серьёзности уведомления
enum class Severity
{
    INFO,       // Информационное сообщение
    WARNING,    // Предупреждение
    CRITICAL    // Критическая ошибка
};

class Alert
{
public:
    // Конструктор
    Alert(const std::string& id,
        const std::string& sensorId,
        const std::string& message,
        Severity severity);

    // Деструктор
    ~Alert();

    // Методы уведомления
    void SendTextNotification() const;
    void SendSoundNotification() const;

    // Преобразование уровня важности в строку
    static std::string SeverityToString(Severity severity);

private:
    std::string m_id;        // ID уведомления
    std::string m_sensorId;  // ID сенсора, вызвавшего тревогу
    std::string m_message;   // Текст сообщения
    Severity m_severity;     // Уровень серьёзности (enum class)
};
