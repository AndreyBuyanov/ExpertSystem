#pragma once

#include <string>
#include <memory>

namespace ES
{

/**
 * Интерфейс экспертной системы.
 */
class IExpertSystem
{
public:
    virtual ~IExpertSystem() = default;

    /**
     * Загрузка экспертной системы.
     * 
     * \param configPath
     * \return 
     */
    virtual void Load(
        const std::string& configPath) noexcept(false) = 0;

    /**
     * Получение названия экспертной системы.
     *
     * \return Название экспертной системы
     */
    virtual std::string GetName() const = 0;

    /**
     * Получение текущего результата.
     *
     * \return Ответ экспертной системы (вопрос либо ответ)
     */
    virtual std::string GetCurrentData() const = 0;

    /**
     * Подача ответа в экспертную систему.
     *
     * \return true - если ответ был принят экспертной системой
     */
    virtual bool SetAnswer(const int value) = 0;

    /**
     * Проверка завершения работы экспертной системы.
     * Экспертная система завершит свою работу, если получен ответ.
     *
     * \return true - если экспертная система завершила работу
     */
    virtual bool IsFinished() const = 0;

    /**
     * Сброс экспертной системы в начальное состояние.
     *
     * \return 
     */
    virtual void Reset() = 0;
};

/**
 * Создание экспертной системы по умолчанию.
 */
std::unique_ptr<IExpertSystem> CreateExpertSystem();

}
