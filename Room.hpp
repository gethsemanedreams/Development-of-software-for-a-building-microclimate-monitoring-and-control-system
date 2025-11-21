#pragma once
#include <vector>
#include "Sensor.hpp"

//
// Класс Room описывает помещение, в котором установлены датчики.
// Содержит список указателей на объекты Sensor.
//
class Room
{
private:
	std::string m_name;            // Название помещения
	std::vector<Sensor*> m_sensors; // Коллекция датчиков (указатели)

public:
	Room(const std::string& name);
	~Room();

	// Добавляет датчик в список помещения.
	void AddSensor(Sensor* sensor);

	// Проверяет все датчики (считывает и выводит значения).
	void CheckAllSensors();
};
