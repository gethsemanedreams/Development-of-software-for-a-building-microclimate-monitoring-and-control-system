#pragma once
#include "Sensor.hpp"

//
// Класс конкретного датчика температуры.
// Реализует чтение значений и проверку выхода за допустимые пределы.
//
class TemperatureSensor : public Sensor
{
private:
	float m_thresholdMin;  // Минимально допустимая температура
	float m_thresholdMax;  // Максимально допустимая температура

public:
	TemperatureSensor(const std::string& id, float min, float max);
	~TemperatureSensor();

	// Считывает текущее значение температуры (эмуляция случайным числом).
	float ReadValue() override;

	// Проверяет, находится ли значение вне допустимого диапазона.
	bool IsOutOfRange() const;

	// Возвращает текстовое описание состояния ("NORMAL" / "CRITICAL").
	std::string GetWarningLevel() const;
};
