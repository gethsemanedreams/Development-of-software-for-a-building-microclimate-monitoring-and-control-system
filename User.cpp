#include "User.hpp"

User::User(const std::string& id, const std::string& name, const std::string& contact)
	: m_id(id), m_name(name), m_contactInfo(contact)
{
	std::cout << "User created: " << m_name << std::endl;
}

User::~User()
{
	std::cout << "User destroyed: " << m_name << std::endl;
}

void User::ReceiveAlert(const Alert& alert)
{
	std::cout << m_name << " received alert: " << std::endl;
	alert.SendTextNotification();
}

void User::ViewReport()
{
	std::cout << m_name << " is viewing system reports..." << std::endl;
}

void User::SetContactInfo(const std::string& newInfo)
{
	m_contactInfo = newInfo;
	std::cout << "Updated contact info for " << m_name << ": " << m_contactInfo << std::endl;
}
