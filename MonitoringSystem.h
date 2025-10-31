#pragma once
#include "Room.h"
#include "Logger.h"
#include <vector>

//
// Класс MonitoringSystem управляет всеми помещениями и логированием.
// Отвечает за опрос всех датчиков и запись результатов в журнал.
//
class MonitoringSystem
{
private:
	std::vector<Room*> m_rooms; // Список помещений под наблюдением
	Logger m_logger;           // Ссылка на общий логгер (Singleton)

public:
	MonitoringSystem();
	~MonitoringSystem();

	// Добавляет новое помещение в систему.
	void AddRoom(Room* room);

	// Проводит опрос всех датчиков во всех помещениях.
	void PollSensors();
};
