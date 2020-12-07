#include "ExpertSystem.hpp"

#include "IExpertSystemLoader.hpp"

namespace ES
{

/**
 * Создание экспертной системы.
 * 
 * \return Указатель на созданную экспертную систему
 */
std::unique_ptr<IExpertSystem> CreateExpertSystem()
{
    return std::make_unique<ExpertSystem>();
}

/**
 * Загрузка экспертной системы.
 * 
 * \param configPath Путь к конфигурации
 * \return 
 */
void ExpertSystem::Load(
    const std::string& configPath) noexcept(false)
{
    // Создаём загрузчик
    auto loader = CreateExpertSystemLoader();
    // Загружаем
    loader->Load(configPath);
    // Получаем имя
    m_name = loader->GetName();
    // Создаём дерево
    m_tree = std::make_unique<Tree>();
    // Получаем список вопросов
    auto questions = loader->GetQuestions();
    // Добавляем вопросы в дерево
    for (const auto& question : questions) {
        m_tree->AddQuestion(question);
    }
    // Получаем список ответов
    auto answers = loader->GetAnswers();
    // Добавляем ответы в дерево
    for (const auto& answer : answers) {
        m_tree->AddAnswer(answer);
    }
    // Получаем список соединений
    auto connections = loader->GetConnections();
    // Добавляем соединения в дерево
    for (const auto& connection : connections) {
        m_tree->AddConnection(connection);
    }
    // Запоминаем указатель на корень дерева
    currentNode = m_tree->GetRoot();
}

/**
 * Получение названия экспертной системы.
 * 
 * \return Название экспертной системы
 */
std::string ExpertSystem::GetName() const
{
    // Возвращаем название
    return m_name;
}

/**
 * Получаем значение текущего узла дерева.
 * Это может быть вопрос или ответ.
 * Перед вызовом данного метода нужно проверить
 * завершение работы экспертной системы, вызвав
 * метод IsFinished(), поскольку если система уже достигла
 * конечного состояния, то получение значения текущего узла
 * является бессмысленным. В таком случае будет возвращена
 * пустая сторока.
 * 
 * \return Текущее значение узла
 */
std::string ExpertSystem::GetCurrentData() const
{
    // Проверка завершения работы экспертной системы
    if (m_finished) {
        // Система достигла конечного состояния,
        // возвращаем пустую строку.
        return "";
    }
    // Получение значения текущего узла
    std::string result = currentNode->Data();
    // Если текущий узел это ответ,
    if (currentNode->Type() == NodeType::Answer) {
        // то выставляем флаг завершения работы системы
        m_finished = true;
    }
    // Возвращаем результат
    return result;
}

/**
 * Подача ответа в экспертную систему.
 * 
 * \param value Ответ
 * \return Результата обработки ответа.
 */
bool ExpertSystem::SetAnswer(const int value)
{
    // Результат. На данном этапе отрицательный
    bool result = false;
    // Если текущий узел - это вопрос,
    if (currentNode->Type() == NodeType::Question) {
        // кастуем к узлу, имеющим тип вопрос
        auto question = dynamic_cast<Question*>(currentNode);
        // Подаём ответ в узел в надежде получить указатель
        // на следующий узел. Тут, собственно, и происходит
        // переход экспертной системы в новое состояние.
        auto nextNode = question->GetNext(value);
        // Проверяем, что узел, соответствующий ответу найден.
        // Если же узел не найден, значит был подан ответ,
        // на который в экспертной системе не оказалось ответа.
        if (nextNode) {
            // Система перешла в новое состояние.
            // Полученный узел становится текущим
            currentNode = nextNode;
            // Результат - положительный.
            result = true;
        }
    }
    // Возвращаем результат
    return result;
}

/**
 * Проверка завершения работы экспертной системы.
 * 
 * \return true - если экспертная система завершила работу
 */
bool ExpertSystem::IsFinished() const
{
    // Возвращаем значение флага завершения работы
    return m_finished;
}

/**
 * Сброс экспертной системы в начальное состояние.
 * 
 */
void ExpertSystem::Reset()
{
    // Делаем текущим узлом корень дерева
    currentNode = m_tree->GetRoot();
    // Сбрасываем флаг завершения работы системы
    m_finished = false;
}

}
