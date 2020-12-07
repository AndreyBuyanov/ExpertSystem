#pragma once

#include "Types.hpp"

#include <map>

namespace ES
{

/**
 * Базовый класс для узла дерева.
 */
class BasicNode
{
public:
    /**
     * Конструктор.
     * 
     * \param config Конфигурация узла
     */
    BasicNode(
        const NodeConfig& config):
        m_config(config) {}

    /**
     * Деструктор.
     * 
     */
    virtual ~BasicNode() {}

    /**
     * Получение данных, хранящихся в узле.
     * 
     * \return Данные, хранящиеся в узле
     */
    const node_data_t& Data() const noexcept
    {
        return m_config.data;
    }

    /**
     * Получение идентификатора узла.
     * 
     * \return Идентификатор узла
     */
    node_id_t ID() const noexcept
    {
        return m_config.id;
    }

    /**
     * Получение типа узла.
     * 
     * \return Тип узла
     */
    virtual NodeType Type() const noexcept = 0;

protected:
    // Конфигурация узла
    NodeConfig m_config;
};

/**
 * Класс для узла, имеющего тип "Вопрос".
 */
class Question final:
    public BasicNode
{
public:

    /**
     * Конструктор.
     * 
     * \param config Конфигурация узла
     */
    Question(
        const NodeConfig& config):
        BasicNode(config){}

    /**
     * Деструктор.
     * 
     */
    ~Question() = default;

    /**
     * Переход к следующему дочернему узлу
     * согласно значению (ответу на текущий вопрос).
     * 
     * \param answerValue Ответ
     * \return Дочерний узел, соответствующий ответу.
     * Это может быть другой вопрос, либо ответ, либо узла может не существовать.
     * Если узла не существует, то это говорит о неполноте информации в эеспертной системе.
     * В таком случае следует добавить отсутствующий узел в конфигурационный файл.
     */
    BasicNode* GetNext(
        const int answerValue) const noexcept
    {
        // Перебираем все дочерние узлы
        // node - текущий дочерний узел
        // predicat - предикат, соответствующий дочернему узлу
        for (const auto& [node, predicat] : m_childrens) {
            // Применяем значение ответа к предикату текущего дочернего узла
            if (predicat(answerValue)) {
                // Значение предиката соответствует текущему узлу.
                // Возвращаем его в качестве результата
                return node;
            }
        }
        // Среди дочерних узлов не удалось найти узел,
        // соответствующий предикату
        return nullptr;
    }

    /**
     * Добавление нового соединения к текущему узлу.
     * 
     * \param dst Узел, который станет дочерним текущему узлу
     * \param predicat Предикат, соответствующий добавляемому узлу
     * \return 
     */
    void AddConnection(
        BasicNode* dst,
        const node_predicat_t& predicat) noexcept
    {
        m_childrens[dst] = predicat;
    }

    // BasicNode
    /**
     * Получение типа узла.
     * 
     * \return 
     */
    NodeType Type() const noexcept override
    {
        // Текущий узел - это вопрос
        return NodeType::Question;
    }
private:
    // Дочерние узлы
    // Ключ - указатель на дочерний узел
    // Значение - предикат, соответствующий дочернему узлу
    std::map<BasicNode*, node_predicat_t> m_childrens;
};

/**
 * Класс для узла, имеющего тип "Ответ".
 * В отличии от "Вопроса" у "Ответа" нет дочерних узлов.
 * "Ответ" - это сигнал того, что экспертная система нашла
 * ответ на поставленную задачу и готова завершить свою работу,
 * и, собственно, этот тип узла и будет использоваться
 * в качестве критерия завершения работы экспертной системы.
 */
class Answer final:
    public BasicNode
{
public:

    /**
     * Конструктор.
     * 
     * \param config Конфигурация узла
     */
    Answer(
        const NodeConfig& config):
        BasicNode(config){}

    /**
     * Деструктор.
     * 
     */
    ~Answer() = default;

    // BasicNode
    /**
     * Получение типа узла.
     * 
     * \return Тип узла
     */
    NodeType Type() const noexcept override
    {
        // Текущий узел - это ответ
        return NodeType::Answer;
    }
};

}
