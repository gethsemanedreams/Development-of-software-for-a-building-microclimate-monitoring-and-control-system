#pragma once
#include <string>
#include <vector>

class Logger
{
public:
    // Получение единственного экземпляра
    static Logger& GetInstance();

    // Записать сообщение в лог
    void Log(const std::string& message);

    // Вывод логов на экран
    void PrintLog() const;

    // Сохранение логов в файл
    void SaveToFile(const std::string& filename = "log.txt") const;

private:
    Logger() = default;  // приватный конструктор

    // Запрещаем копирование и присваивание
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    std::vector<std::string> m_log;   // внутренний буфер логов
};