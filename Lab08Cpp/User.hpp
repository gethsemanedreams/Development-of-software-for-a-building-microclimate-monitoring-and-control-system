#pragma once
#include <string>
#include <iostream>
#include "Alert.hpp"

/// \brief Простой пользователь системы.
class User
{
protected:
    std::string m_id;
    std::string m_name;
    std::string m_email;

public:
    User(const std::string& id,
         const std::string& name,
         const std::string& email)
        : m_id(id)
        , m_name(name)
        , m_email(email)
    {
        std::cout << "User created: " << m_name << std::endl;
    }

    User(const User&) = default;
    virtual ~User() = default;

    virtual void ReceiveAlert(const Alert& alert) const
    {
        std::cout << "User '" << m_name << "' received alert:\n";
        alert.SendTextNotification();
    }

    const std::string& GetName() const { return m_name; }
};

/// \brief Пример производного класса пользователя.
///
/// ЛР-6 (для C++ можно показать ещё один пример наследования).
class AdminUser : public User
{
    int m_priority{};

public:
    AdminUser(const std::string& id,
              const std::string& name,
              const std::string& email,
              int priority)
        : User(id, name, email)
        , m_priority(priority)
    {
        std::cout << "AdminUser created: " << m_name
                  << " with priority " << m_priority << std::endl;
    }

    void ReceiveAlert(const Alert& alert) const override
    {
        std::cout << "[ADMIN] ";
        User::ReceiveAlert(alert);
    }
};
