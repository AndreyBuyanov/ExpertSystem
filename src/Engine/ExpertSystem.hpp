#pragma once

#include "IExpertSystem.hpp"

#include "Tree.hpp"

namespace ES
{

/**
 * Реализация экспертной системы.
 * Работа экспертной системы сводится к
 * последовательному прохождению по дереву вопросов
 * и ответов. Для этого и используется дерево.
 */
class ExpertSystem final:
    public IExpertSystem
{
public:
    // Реализация интерфейса IExpertSystem

    void Load(
        const std::string& configPath) noexcept(false) override;

    std::string GetName() const override;

    std::string GetCurrentData() const override;

    bool SetAnswer(
        const int value) override;

    bool IsFinished() const override;

    void Reset() override;
private:
    // Дерево
    std::unique_ptr<Tree> m_tree;
    // Имя экспертной системы
    std::string m_name;
    // Текущий узел дерева
    mutable BasicNode* currentNode = nullptr;
    // Флаг, показывающий окончание работы экспертной системы.
    // Флаг будет выставлен, когда в процессе движения по дереву
    // текущий узел будет соответствовать узлу с типом "Ответ",
    // либо в ответ не будет найден в экспертной системе.
    mutable bool m_finished = false;
};

}
