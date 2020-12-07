#pragma once

#include <string>
#include <functional>

namespace ES
{

// Тип для идентификатора узла
using node_id_t = int;
// Тип данных, хранящихся в узле
using node_data_t = std::string;
// Предикат для ответа
using node_predicat_t = std::function<bool(const int)>;

// Тип узла
enum class NodeType
{
    Question,   // Вопрос
    Answer      // Ответ
};

// Конфигурация узла
struct NodeConfig
{
    // Идентификатор узла
    node_id_t id = -1;
    // Данные, хранящиеся в узле
    node_data_t data;

    // Конструктор
    NodeConfig(
        const node_id_t _id,
        const node_data_t& _data):
        id(_id),
        data(_data) {}
};

// Конфигурация соединения
struct ConnectionConfig
{
    // Идентификатор источника
    node_id_t src = -1;
    // Идентификатор приёмника
    node_id_t dst = -1;
    // Предикат соединения
    node_predicat_t predicat;

    // Конструктор
    ConnectionConfig(
        const node_id_t _src,
        const node_id_t _dst,
        const node_predicat_t _predicat):
        src(_src),
        dst(_dst),
        predicat(_predicat) {}
};

}
