#pragma once
#include "Sensor.hpp"
#include <random>

/// \brief Датчик температуры.
/// Наследуется от Sensor и добавляет диапазон допустимых значений.
///
/// ЛР-6:
///  * переопределяем виртуальные методы;
///  * в Calibrate() вызываем базовую реализацию Sensor::Calibrate();
///  * реализуем виртуальный Clone();
///  * перегружаем оператор присваивания от базового класса Sensor;
///  * определяем метод TypeName() с той же сигнатурой, но без virtual
///    (демонстрация отличия от виртуального метода).
class TemperatureSensor : public Sensor
{
protected:
    float m_min{};
    float m_max{};

public:
    TemperatureSensor(const std::string& id,
                      const std::string& name,
                      float min,
                      float max);

    // Конструктор копирования по умолчанию нам подходит.
    TemperatureSensor(const TemperatureSensor&) = default;

    ~TemperatureSensor() override = default;

    float ReadValue() override;
    bool  CheckStatus() const override;
    void  Calibrate() override;
    std::string Describe() const override;
    Sensor* Clone() const override;

    /// \brief Перегрузка оператора присваивания от базового класса.
    ///
    /// ЛР-6: объекту производного класса (TemperatureSensor) присваиваем
    /// состояние объекта базового класса Sensor.
    TemperatureSensor& operator=(const Sensor& base);

    /// \brief Невиртуальная функция с тем же именем, что и у базового класса.
    ///
    /// При вызове через указатель/ссылку на базовый класс будет использоваться
    /// реализация Sensor::TypeName(), а при вызове по объекту производного —
    /// эта функция.
    std::string TypeName() const;
};
