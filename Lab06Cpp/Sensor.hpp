#pragma once
#include <string>
#include <memory>
#include <iostream>

/// \brief Абстрактный базовый класс для любых датчиков.
///
/// ЛР-6:
///  * демонстрируем protected-поля (к ним имеют доступ производные классы);
///  * делаем деструктор виртуальным (важно при удалении через указатель на базу);
///  * вводим виртуальные методы (ReadValue, Describe, Clone);
///  * демонстрируем вызов виртуальной функции из невиртуальной (PrintWithHeader);
///  * показываем разницу между виртуальной и невиртуальной функцией (Describe vs TypeName);
///  * добавляем метод SetStatus с использованием указателя this.
class Sensor
{
protected:
    std::string m_id;       ///< Идентификатор датчика (например, "T1").
    std::string m_name;     ///< Человекочитаемое имя.
    std::string m_unit;     ///< Единица измерения (например, "°C").
    float       m_lastValue{}; ///< Последнее измеренное значение.
    std::string m_status;   ///< Статус датчика ("OK", "ERROR" и т.п.).

public:
    /// \brief Конструктор базового класса.
    Sensor(const std::string& id,
           const std::string& name,
           const std::string& unit);

    /// \brief Виртуальный деструктор.
    ///
    /// ЛР-6: благодаря virtual при delete basePtr, где basePtr указывает
    /// на объект производного класса, вызывается деструктор именно производного класса.
    virtual ~Sensor() = default;

    // Геттеры
    const std::string& GetId()    const { return m_id; }
    const std::string& GetName()  const { return m_name; }
    const std::string& GetUnit()  const { return m_unit; }
    float              GetLastValue() const { return m_lastValue; }
    const std::string& GetStatus() const { return m_status; }

    /// \brief Чтение нового значения датчика (виртуально, чистая абстракция).
    virtual float ReadValue() = 0;

    /// \brief Проверка состояния датчика (виртуально, но не чистое).
    virtual bool CheckStatus() const;

    /// \brief Калибровка датчика (виртуально, может переопределяться).
    virtual void Calibrate();

    /// \brief Описание датчика (виртуальная функция).
    ///
    /// ЛР-6: будет переопределяться в производных классах.
    virtual std::string Describe() const;

    /// \brief Невиртуальная обёртка, которая внутри вызывает виртуальный Describe().
    ///
    /// Демонстрирует косвенный вызов виртуальной функции через невиртуальную.
    void PrintWithHeader() const;

    /// \brief Невиртуальная функция, демонстрирующая "статический" полиморфизм.
    ///
    /// В производных классах мы объявим метод с тем же именем и сигнатурой,
    /// но без virtual. При вызове через указатель на базовый класс будет
    /// вызываться именно эта реализация.
    std::string TypeName() const;

    /// \brief Виртуальный метод клонирования (прототипный подход).
    ///
    /// ЛР-6: используется для глубокого копирования объектов при клонировании Room.
    virtual Sensor* Clone() const = 0;

    /// \brief Меняет статус и возвращает *this (использование указателя this).
    ///
    /// Позволяет писать цепочки вида:
    ///   sensor.SetStatus("ERROR").Calibrate();
    Sensor& SetStatus(const std::string& status);
};

/// Умный указатель на Sensor, чтобы не управлять памятью вручную.
using SensorPtr = std::shared_ptr<Sensor>;
