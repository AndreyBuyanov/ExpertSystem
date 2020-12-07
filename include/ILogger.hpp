#pragma once

#include <string>

namespace ES
{

/**
 * Уровень лога.
 */
enum class LogLevel
{
    Error,      // Ошибка
    Warning,    // Предупреждение
    Info        // Информация
};

/**
 * Интерфейс логгера.
 */
class ILogger
{
public:
    virtual ~ILogger() = default;

    /**
     * Запись в лог.
     * 
     * \param level Уровень лога
     * \param log Сообщение
     * \return 
     */
    virtual void Log(
        const LogLevel level,
        const std::string& log) = 0;
};

/**
 * Получение экземпляра логгера по умолчанию.
 */
ILogger* DefaultLoggerInstance();

#define logger DefaultLoggerInstance()

}
