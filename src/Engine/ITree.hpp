#pragma once

#include "Node.hpp"

namespace ES
{

/**
 * Интерфейс дерева.
 */
class ITree
{
public:
    virtual ~ITree() = default;

    /**
     * Получение корня дерева.
     * 
     * \return Корень дерева
     */
    virtual BasicNode* GetRoot() const noexcept = 0;

    /**
     * Добавление узла, имеющего тип "Вопрос".
     * 
     * \param question Конфигурация узла
     * \return 
     */
    virtual void AddQuestion(
        const NodeConfig& question) noexcept = 0;

    /**
     * Добавление узла, имеющего тип "Ответ".
     * 
     * \param answer Конфигурация узла
     * \return 
     */
    virtual void AddAnswer(
        const NodeConfig& answer) noexcept = 0;

    /**
     * Добавление соединения между узлами.
     * 
     * \param connection Конфигурация соединения
     * \return 
     */
    virtual void AddConnection(
        const ConnectionConfig& connection) noexcept = 0;
};

}
