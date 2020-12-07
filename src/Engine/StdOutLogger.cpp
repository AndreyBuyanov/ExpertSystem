#include "StdOutLogger.hpp"

#include <memory>
#include <iostream>

namespace ES
{

/**
 * Получение экземпляра логгера по умолчанию.
 * 
 * \return Экземпляр логгера по умолчанию
 */
ILogger* DefaultLoggerInstance()
{
    // Указатель на логгер по умолчанию
    static std::unique_ptr<ILogger> defaultLogger;
    // Если логгер ещё не создан,
    if (!defaultLogger) {
        // создадим его
        defaultLogger = std::make_unique<StdOutLogger>();
    }
    // Вернём указатель на логгер
    return defaultLogger.get();
}

/**
 * Преобразование уровня лога в строку.
 * 
 * \param logLevel Уровень лога
 * \return Строковое представление уровня лога
 */
static std::string LogLevelToString(
    const LogLevel logLevel)
{
    switch (logLevel) {
    case LogLevel::Error:
        return "[ERROR  ]";
    case LogLevel::Warning:
        return "[WARNING]";
    case LogLevel::Info:
        return "[INFO   ]";
    }
}

/**
 * Запись в лог.
 * 
 * \param level Уровень лога
 * \param log Сообщение
 * \return 
 */
void StdOutLogger::Log(
    const LogLevel level,
    const std::string& log)
{
    // Запираем мьютекс, чтобы монопольно завладеть кодом ниже
    std::unique_lock<decltype(m_logLock)> lock;
    // Пишем сообщение в стандартный вывод, выведя перед сообщением
    // уровень лога
    std::cout << LogLevelToString(level) << ": " << log << std::endl;
}

}
