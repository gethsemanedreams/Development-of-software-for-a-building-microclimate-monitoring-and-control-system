#include "User.hpp"

User::User(const std::string& id,
           const std::string& name,
           const std::string& email)
    : m_id(id)
    , m_name(name)
    , m_email(email)
{
}

User::User(const User& other)
    : m_id(other.m_id)
    , m_name(other.m_name)
    , m_email(other.m_email)
{
}

void User::ReceiveAlert(const Alert& alert) const
{
    std::cout << "User '" << m_name << "' (" << m_email << ") received alert:\n"
              << "  " << alert << "\n";
}

