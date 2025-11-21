#pragma once
#include <string>
#include <iostream>

//
// Класс Measurement представляет одно измерение,
// выполненное датчиком. Используется для записи истории значений.
//
class Measurement
{
private:
	std::string m_sensorId;   // Идентификатор датчика
	float m_value;            // Измеренное значение
	std::string m_timestamp;  // Время измерения (в виде строки)

public:
	Measurement(const std::string& sensorId, float value, const std::string& timestamp);
	~Measurement();

	// Проверяет, находится ли значение за пределами нормы.
	bool IsAnomalous(float min, float max) const;

	// Возвращает строковое представление измерения.
	std::string ToString() const;
};

