#pragma once

#include "Node.hpp"
#include "ITree.hpp"

#include <map>
#include <string>
#include <memory>
#include <functional>

namespace ES
{

/**
 * Реализация дерева.
 */
class Tree final:
    public ITree
{
public:
    virtual ~Tree() = default;

    // Реализация интерфейса ITree

    BasicNode* GetRoot() const noexcept override;

    void AddQuestion(
        const NodeConfig& question) noexcept override;

    void AddAnswer(
        const NodeConfig& answer) noexcept override;

    void AddConnection(
        const ConnectionConfig& connection) noexcept override;
private:
    // Хранилище для узлов
    // Ключ - идентификатор узла
    // Значение - умный указатель на узел
    std::map<node_id_t, std::unique_ptr<BasicNode>> m_nodesStorage;
    // Указатель на корень дерева
    BasicNode* m_root = nullptr;
};

}
