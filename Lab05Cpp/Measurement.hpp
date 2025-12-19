#pragma once
#include <string>
#include <iostream>
#include <chrono>

/// \brief Структура одного измерения.
///
/// Здесь демонстрируем:
///  * конструктор копирования;
///  * перегрузку операторов <<, < и ==.
class Measurement
{
private:
    std::string m_sensorId;
    float       m_value;
    std::chrono::system_clock::time_point m_timestamp;

public:
    Measurement(const std::string& sensorId,
                float value,
                std::chrono::system_clock::time_point timestamp);

    Measurement(const Measurement& other);

    const std::string& GetSensorId() const { return m_sensorId; }
    float GetValue() const { return m_value; }
    std::chrono::system_clock::time_point GetTimestamp() const { return m_timestamp; }

    friend std::ostream& operator<<(std::ostream& os, const Measurement& m);

    bool operator<(const Measurement& other) const;
    bool operator==(const Measurement& other) const;
};

