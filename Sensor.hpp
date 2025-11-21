#pragma once
#include <string>

//
// Абстрактный базовый класс для всех типов датчиков.
// Определяет общие свойства (идентификатор, имя, единицы измерения)
// и интерфейс для чтения значения, проверки состояния и калибровки.
//
class Sensor
{
protected:
	std::string m_id;       // Уникальный идентификатор датчика
	std::string m_name;     // Название датчика
	std::string m_unit;     // Единица измерения (°C, %, ppm и т.д.)
	float m_lastValue;      // Последнее измеренное значение
	std::string m_status;   // Состояние датчика (OK, ERROR)

public:
	Sensor();
	Sensor(const std::string& id, const std::string& name, const std::string& unit);
	virtual ~Sensor();

	// Абстрактный метод — должен быть реализован в наследниках.
	virtual float ReadValue() = 0;

	// Проверяет работоспособность датчика.
	virtual bool CheckStatus();

	// Выполняет калибровку датчика.
	virtual void Calibrate();
};