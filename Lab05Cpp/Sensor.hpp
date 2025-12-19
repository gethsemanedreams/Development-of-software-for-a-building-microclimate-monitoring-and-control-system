#pragma once
#include <string>
#include <memory>

/// \brief Абстрактный базовый класс для любых датчиков.
///
/// Здесь мы:
///  * используем std::string вместо сырого char[];
///  * демонстрируем вызов конструктора базового класса из конструкторов потомков;
///  * используем this в методе SetStatus для "цепочек" вызовов.
class Sensor
{
protected:
    std::string m_id;       ///< Идентификатор датчика (например, "T1").
    std::string m_name;     ///< Человекочитаемое имя.
    std::string m_unit;     ///< Единица измерения (например, "°C").
    float       m_lastValue {0.0f};
    std::string m_status {"OK"};

public:
    Sensor(const std::string& id,
           const std::string& name,
           const std::string& unit);

    virtual ~Sensor() = default;

    /// Конструктор копирования.
    Sensor(const Sensor& other);

    const std::string& GetId()   const { return m_id; }
    const std::string& GetName() const { return m_name; }
    const std::string& GetUnit() const { return m_unit; }
    float GetLastValue()         const { return m_lastValue; }
    const std::string& GetStatus() const { return m_status; }

    /// \brief Абстрактное чтение значения.
    virtual float ReadValue() = 0;

    /// \brief Проверка состояния датчика.
    virtual bool CheckStatus() const;

    /// \brief "Калибровка" датчика.
    virtual void Calibrate();

    /// \brief Метод, использующий указатель this.
    /// Меняет статус и возвращает ссылку на *this, чтобы можно было писать
    /// цепочки вида sensor.SetStatus("ERROR").Calibrate();
    Sensor& SetStatus(const std::string& status);
};

using SensorPtr = std::shared_ptr<Sensor>;

