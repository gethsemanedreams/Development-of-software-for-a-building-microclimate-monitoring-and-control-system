#include "MonitoringSystem.h"
#include "TemperatureSensor.h"
#include "Alert.h"
#include "User.h"
#include "Measurement.h"
#include <iostream>

//
// Тестовый пример демонстрирует:
// - статическую и динамическую инициализацию объектов,
// - работу с указателями и ссылками,
// - использование Singleton (Logger),
// - корректное освобождение памяти.
//
int main()
{
	// --- Статическая инициализация ---
	TemperatureSensor staticSensor("T1", 0.0f, 40.0f);
	staticSensor.ReadValue();

	// --- Динамическая инициализация ---
	Room* room1 = new Room("Server Room");
	room1->AddSensor(new TemperatureSensor("T2", 10.0f, 35.0f));

	// --- Создание системы мониторинга ---
	MonitoringSystem system;
	system.AddRoom(room1);

	// --- Работа по ссылке и указателю ---
	Room& refRoom = *room1;
	Room* ptrRoom = room1;

	refRoom.CheckAllSensors();
	ptrRoom->CheckAllSensors();

	// --- Запуск опроса всей системы ---
	system.PollSensors();

	// --- Вывод лога ---
	//-Здесь в финальной версии будет вывод лога-

	// Создание пользователя
	User user1("U1", "Alice", "alice@example.com");

	// Создание измерения
	Measurement meas("T1", 45.0f, "2025-10-14 10:30");
	std::cout << meas.ToString() << std::endl;

	// Создание предупреждения
	Alert alert1("A1", "T1", "Temperature too high!", "CRITICAL", "2025-10-14 10:31");

	// Пользователь получает уведомление
	user1.ReceiveAlert(alert1);
	alert1.Acknowledge();

	// --- Очистка памяти ---
	delete room1;

	std::cout << "\nProgram finished successfully.\n";
	return 0;
}