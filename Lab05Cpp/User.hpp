#pragma once
#include <string>
#include <iostream>
#include "Alert.hpp"

/// \brief Пользователь системы мониторинга.
class User
{
private:
    std::string m_id;
    std::string m_name;
    std::string m_email;

public:
    User(const std::string& id,
         const std::string& name,
         const std::string& email);

    User(const User& other);

    void ReceiveAlert(const Alert& alert) const;
};

