#include "XmlExpertSystemLoader.hpp"
#include "ILogger.hpp"

#include "pugixml.hpp"

#include <stdexcept>

namespace ES
{

/**
 * Создание загрузчика по умолчанию.
 * 
 * \return Экземпляр загрузчика
 */
std::unique_ptr<IExpertSystemLoader> CreateExpertSystemLoader()
{
    return std::make_unique<XmlExpertSystemLoader>();
}

/**
 * Загрузка экспертной системы из файла конфигурации.
 * 
 * \param configPath путь к файлу конфигурации
 * \return 
 */
void XmlExpertSystemLoader::Load(
    const std::string& configPath) noexcept(false)
{
    // xml-файл
    pugi::xml_document doc;

    // Открываем файл
    pugi::xml_parse_result result = doc.load_file(configPath.c_str());
    // Проверяем результат открытия и парсинга файла
    if (!result) {
        // Что-то пошло не так. Кидаем исключение
        throw std::runtime_error(result.description());
    }

    // Ищем в документе элемент <es>
    auto elEs = doc.child("es");
    if (!elEs) {
        // Элемент <es> не найден. Кидаем исключение
        throw std::runtime_error(
            u8"В конфигурационном файле не найден элемент <es>");
    }

    // Ищем в дочерних элементах элемента <es> элемент <name>
    auto elName = elEs.child("name");
    if (!elName) {
        // Элемент <name> не найден. Кидаем исключение
        throw std::runtime_error(
            u8"В конфигурационном файле не найден элемент <name>");
    }
    // Сохраняем название экспертной системы
    m_name = elName.text().as_string();

    // Ищем в дочерних элементах элемента <es> элемент <tree>
    auto elTree = elEs.child("tree");
    if (!elTree) {
        // Элемент <tree> не найден. Кидаем исключение
        throw std::runtime_error(
            u8"В конфигурационном файле не найден элемент <tree>");
    }
    // Ищем в дочерних элементах элемента <tree> элемент <nodes>
    auto elNodes = elTree.child("nodes");
    if (!elNodes) {
        // Элемент <nodes> не найден. Кидаем исключение
        throw std::runtime_error(
            u8"В конфигурационном файле не найден элемент <nodes>");
    }

    // Проходим по дочерним элементам <node> элемента <nodes>
    for (auto node = elNodes.child("node"); node; node = node.next_sibling("node")) {
        // Считываем атрибут type
        auto nodeType = node.attribute("type");
        if (!nodeType) {
            // Атрибут type не найден. Запишем предупреждение в лог
            logger->Log(LogLevel::Warning,
                u8"У элемента <node> не найден атрибут type");
            // Проигнорируем текущйи элемент и перейдём к следующему элементу
            continue;
        }
        // Считываем атрибут id
        auto nodeID = node.attribute("id");
        if (!nodeID) {
            // Атрибут id не найден. Запишем предупреждение в лог
            logger->Log(LogLevel::Warning,
                u8"У элемента <node> не найден атрибут id");
            // Проигнорируем текущйи элемент и перейдём к следующему элементу
            continue;
        }
        // Считываем данные узла
        auto nodeData = node.text();
        if (!nodeData) {
            // Данных не оказалось. Запишем предупреждение в лог
            logger->Log(LogLevel::Warning,
                u8"Элемент <node> не содержит данных");
            // Проигнорируем текущйи элемент и перейдём к следующему элементу
            continue;
        }
        // Получаем стороковое представление типа узла
        std::string nodeTypeStr = nodeType.as_string();
        if (nodeTypeStr == "question") {
            // Если текущий узел - это вопрос, то добавляем данные этого узла к списку вопросов
            m_questions.emplace_back(nodeID.as_int(), std::string(nodeData.as_string()));
        }
        else if (nodeTypeStr == "answer") {
            // Если текущий узел - это ответ, то добавляем данные этого узла к списку ответов
            m_answers.emplace_back(nodeID.as_int(), nodeData.as_string());
        }
        else {
            // Неизвестный тип узла. Запишем предупреждение в лог
            logger->Log(LogLevel::Warning,
                u8"Элемент <node> имеет неизвестный тип");
        }
    }
    // Ищем в дочерних элементах элемента <tree> элемент <connections>
    auto nodeConnections = elTree.child("connections");
    if (!nodeConnections) {
        // Элемент <connections> не найден. Кидаем исключение
        throw std::runtime_error(
            u8"В конфигурационном файле не найден элемент <connections>");
    }

    // Проходим по дочерним элементам <connection> элемента <connections>
    for (auto connection = nodeConnections.child("connection"); connection; connection = connection.next_sibling("connection")) {
        // Считываем атрибут src
        auto src = connection.attribute("src");
        if (!src) {
            // Атрибут src не найден. Запишем предупреждение в лог
            logger->Log(LogLevel::Warning,
                u8"У элемента <connection> не найден атрибут src");
            // Проигнорируем текущйи элемент и перейдём к следующему элементу
            continue;
        }
        // Считываем атрибут dst
        auto dst = connection.attribute("dst");
        if (!dst) {
            // Атрибут dst не найден. Запишем предупреждение в лог
            logger->Log(LogLevel::Warning,
                u8"У элемента <connection> не найден атрибут dst");
            // Проигнорируем текущйи элемент и перейдём к следующему элементу
            continue;
        }
        // Считываем атрибут predicat
        auto predicat = connection.attribute("predicat");
        if (!predicat) {
            // Атрибут predicat не найден. Запишем предупреждение в лог
            logger->Log(LogLevel::Warning,
                u8"У элемента <connection> не найден атрибут predicat");
            // Проигнорируем текущйи элемент и перейдём к следующему элементу
            continue;
        }
        // Добавляем соединение к списку соединений.
        // Предикат - это функция сравнения числа с заданным в атрибуте predicat.
        // Те если параметр предиката раен 0, то если вызвать данный предикат,
        // передав в него 0, то получим ture.
        // Предикаты понадабятся при хождении по дереву
        m_connections.emplace_back(src.as_int(), dst.as_int(),
            [predicat=predicat.as_int()] (const int value) -> bool
        {
            return value == predicat;
        });
    }
    logger->Log(LogLevel::Info, u8"Экспертная система загружена");
}

}
