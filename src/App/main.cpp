#include <iostream>

#if defined(WIN32)
#   define WIN32_LEAN_AND_MEAN
#   include <Windows.h>
#endif

#include "IExpertSystem.hpp"
#include "ILogger.hpp"

/**
 * Запуск экспертной системы
 * 
 * \param config путь к файлу конфигурации
 */
void Run(const std::string& config)
{
    // Создаём экспертную систему
    auto es = ES::CreateExpertSystem();
    // Загружаем из файла конфигурации
    es->Load(config);
    // Выводим название экспертной системы
    std::cout << "~~~ " << es->GetName() << " ~~~" << std::endl;
    // TODO: Вынести варианты ответов в конфигурационный файл
    std::cout << u8"Варианты ответов: 0 - нет, 1 - да." << std::endl;
    // Будем крутиться в бесконечном цикле
    while (true) {
        // Получаем значение текущего узла
        auto current = es->GetCurrentData();
        // Выводим значение текущего узла в стандартный вывод
        std::cout << current << std::endl;
        // Проверяем окончание работы системы
        if (es->IsFinished()) {
            // Текущий узел системы - это ответ. Система завершила свою работу
            // Спрашиваем польлзователя
            std::cout << u8"Введите y для завершения работы, либо любой символ для продолжения." << std::endl;
            char e;
            std::cin >> e;
            if (e == 'y') {
                // Выходим из цикла и завершаем работу
                break;
            } else {
                // Пользователь решил воспользоваться системой ещё раз
                // Сбрасываем состояние системы в начальное
                es->Reset();
                // и переходим к новой итерации
                continue;
            }
        }
        // Текуший узел - это вопрос.
        // Попросим пользователя ввести ответ.
        int a;
        std::cin >> a;
        // Подаём ответ в систему
        if (!es->SetAnswer(a)) {
            // Ответ оказался неправильнымю Выводим сообщение
            std::cout << u8"Неверный ответ. Попробуйте ещё раз" << std::endl;
        }
    }
}

int main (int argc, char *argv[]){
    // Костыль для винды
#if defined(WIN32)
    SetConsoleOutputCP(65001);
#endif
    // Ожидаем, что нам передали путь к конфигурационному файлу
    if (argc < 2) {
        // Выводим сообщение
        std::cout << "Usage: App [config_file]" << std::endl;
        return EXIT_FAILURE;
    }
    try {
        // Запускаем экспертную систему, передав в неё путь к конфигурационному файлу
        Run(argv[1]);
    }
    catch (const std::exception& ex) {
        // В процессе работы системы произошла критическая ошибка.
        // Запишем информацию в лог и завершим работу приложения.
        ES::logger->Log(ES::LogLevel::Error, ex.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
