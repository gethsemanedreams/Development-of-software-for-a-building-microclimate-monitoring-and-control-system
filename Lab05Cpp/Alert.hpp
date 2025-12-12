#pragma once
#include <string>
#include <iostream>

/// \brief Уровень серьёзности оповещения.
/// Это обычное перечисление, его строковое представление
/// мы будем получать через статический метод Alert::SeverityToString.
enum class Severity
{
    Info,       ///< Информационное сообщение.
    Warning,    ///< Предупреждение.
    Critical    ///< Критическая ситуация.
};

/// \brief Класс Alert описывает одно оповещение для пользователя.
///
/// В рамках ЛР-5:
///  * демонстрируем использование std::string;
///  * демонстрируем перегрузку оператора вывода << (friend-функция);
///  * демонстрируем статический метод (SeverityToString).
class Alert
{
private:
    std::string m_id;        ///< Идентификатор оповещения (например, "A1").
    std::string m_sensorId;  ///< Идентификатор датчика-источника (например, "T1").
    std::string m_message;   ///< Текст сообщения.
    Severity    m_severity;  ///< Уровень серьёзности.

public:
    Alert(const std::string& id,
          const std::string& sensorId,
          const std::string& message,
          Severity severity);

    /// Конструктор копирования (требование ЛР-5).
    Alert(const Alert& other);

    const std::string& GetId()        const { return m_id; }
    const std::string& GetSensorId()  const { return m_sensorId; }
    const std::string& GetMessage()   const { return m_message; }
    Severity            GetSeverity() const { return m_severity; }

    /// \brief Текстовое оповещение в консоль.
    void SendTextNotification() const;

    /// \brief "Звуковое" оповещение.
    /// Для лабораторной просто выводим дополнительный текст.
    void SendSoundNotification() const;

    /// \brief Статический метод: перевод Severity -> строка.
    /// Это пример "разумного использования" static-метода в C++.
    static std::string SeverityToString(Severity severity);

    /// \brief Дружественная функция для красивого вывода Alert.
    /// Показываем пример friend + перегрузка оператора <<.
    friend std::ostream& operator<<(std::ostream& os, const Alert& a);
};

