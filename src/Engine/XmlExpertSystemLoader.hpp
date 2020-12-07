#pragma once

#include "IExpertSystemLoader.hpp"

namespace ES
{

/**
 * Реализация загрузчика экспертной системы,
 * загружающего конфигурацию из xml-файла.
 * Пример простой минимальной конфигурации из одного вопроса
 * и двух ответов:
 * <?xml version="1.0" encoding="UTF-8"?> 
 * <es>
 *     <name>Диагностика здоровья</name>
 *     <tree>
 *         <nodes>
 *             <node type="question" id="1">У вас болит голова?</node>
 *             <node type="answer" id="2">Посетите врача</node>
 *             <node type="answer" id="3">Вы здоровы!</node>
 *         </nodes>
 *         <connections>
 *             <connection src="1" dst="2" predicat="1" />
 *             <connection src="1" dst="3" predicat="0" />
 *         </connections>
 *     </tree>
 * </es>
 */
class XmlExpertSystemLoader final :
    public IExpertSystemLoader
{
public:
    virtual ~XmlExpertSystemLoader() = default;

    // Реализация интерфейса IExpertSystemLoader
    void Load(
        const std::string& configPath) noexcept(false);

    std::string GetName() const noexcept
    {
        return m_name;
    }

    std::vector<NodeConfig> GetQuestions() const noexcept
    {
        return m_questions;
    }

    std::vector<NodeConfig> GetAnswers() const noexcept
    {
        return m_answers;
    }

    std::vector<ConnectionConfig> GetConnections() const noexcept
    {
        return m_connections;
    }
private:
    // Название экспертной системы
    std::string m_name;
    // Вопросы
    std::vector<NodeConfig> m_questions;
    // Ответы
    std::vector<NodeConfig> m_answers;
    // Соединения
    std::vector<ConnectionConfig> m_connections;
};

}
