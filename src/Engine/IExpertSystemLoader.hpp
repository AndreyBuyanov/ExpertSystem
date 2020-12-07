#pragma once

#include "Types.hpp"

#include <vector>
#include <memory>
#include <string>

namespace ES
{

/**
 * Интерфейс загрузчика экспертной системы.
 */
class IExpertSystemLoader
{
public:
    virtual ~IExpertSystemLoader() = default;

    /**
     * Загрузка экспертной системы из файла конфигурации.
     * 
     * \param configPath путь к файлу конфигурации
     * \return 
     */
    virtual void Load(
        const std::string& configPath) noexcept(false) = 0;

    /**
     * Получение имени экспертной системы.
     * Перед вызовом данного метода экспертная система должна быть загружена.
     * 
     * \return Имя экспертной системы
     */
    virtual std::string GetName() const noexcept = 0;

    /**
     * Получение загруженных вопросов.
     * Перед вызовом данного метода экспертная система должна быть загружена.
     * 
     * \return Загруженные вопросы
     */
    virtual std::vector<NodeConfig> GetQuestions() const noexcept = 0;

    /**
     * Получение загруженных ответов.
     * Перед вызовом данного метода экспертная система должна быть загружена.
     * 
     * \return Загруженные ответы
     */
    virtual std::vector<NodeConfig> GetAnswers() const noexcept = 0;

    /**
     * Получение загруженных соединений узлов.
     * Перед вызовом данного метода экспертная система должна быть загружена.
     * 
     * \return Загруженные соединения узлов
     */
    virtual std::vector<ConnectionConfig> GetConnections() const noexcept = 0;
};

/**
 * Создание загрузчика по умолчанию.
 *
 * \return Экземпляр загрузчика
 */
std::unique_ptr<IExpertSystemLoader> CreateExpertSystemLoader();

}
