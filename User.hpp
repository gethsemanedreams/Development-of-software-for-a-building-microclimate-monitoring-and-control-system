#pragma once
#include <string>
#include <iostream>
#include "Alert.hpp"

//
// Класс User описывает пользователя системы мониторинга.
// Пользователь может получать и подтверждать предупреждения.
//
class User
{
private:
	std::string m_id;          // Уникальный идентификатор пользователя
	std::string m_name;        // Имя пользователя
	std::string m_contactInfo; // Контактная информация (e-mail / телефон)

public:
	User(const std::string& id, const std::string& name, const std::string& contact);
	~User();

	// Получает уведомление о тревоге.
	void ReceiveAlert(const Alert& alert);

	// Просматривает сохранённые отчёты (эмуляция).
	void ViewReport();

	// Изменяет контактную информацию.
	void SetContactInfo(const std::string& newInfo);
};

