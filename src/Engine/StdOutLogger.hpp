#pragma once

#include "ILogger.hpp"

#include <mutex>

namespace ES
{

/**
 * Класс логгера, выводящего сообщения в стандартный вывод.
 */
class StdOutLogger final:
    public ILogger
{
public:
    virtual ~StdOutLogger() = default;

    // Реализация интерфейса ILogger

    void Log(
        const LogLevel level,
        const std::string& log);
private:
    // Мьютекс, обеспечивающий монопольную запись в стандартный вывод
    std::mutex m_logLock;
};

}
