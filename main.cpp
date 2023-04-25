﻿#include "SecondaryFunction.h"
#include "ChainOfResponsibility.h"

/*
Задание 3. Паттерн «Цепочка ответственности»
Продолжаем тему с реализацией системы логирования в соответствии
с разными паттернами проектирования.

В задании нужно реализовать сообщение о логировании с типом
сообщения и самим сообщением:

class LogMessage {
public:
    Type type() const;
    const std::string& message() const;
};

Всего должно быть четыре типа сообщений:
- предупреждение,
- ошибка,
- фатальная ошибка,
- неизвестное сообщение.

Далее нужно добавить обработчиков для разных типов, которые будут
обрабатывать сообщения по приоритету:
- фатальная ошибка,
- ошибка,
- предупреждение,
- неизвестное сообщение.

Каждый обработчик умеет:
- обрабатывать сообщение только определённого типа,
- передавать сообщение следующему обработчику.

Вот что обработчик должен уметь в зависимости от типа сообщения.
- Обработчик фатальной ошибки должен выбросить исключение с текстом сообщения,
	потому что предполагается, что программа должна прекратить выполнение
	после возникновения фатальной ошибки.
- Обработчик обычной ошибки должен записать её в файл по указанному пути.
- Обработчик предупреждения должен напечатать сообщение в консоль.
- Обработчик неизвестного сообщения должен выбросить исключение с текстом
	о необработанном сообщении.
*/

int main(int argc, char** argv)
{
	printHeader(L"Задание 3. Паттерн «Цепочка ответственности»");

	auto root = std::make_unique<View>(0, 0, 256, 256); // Создаём основное окошко
	auto button = std::make_unique<Button>(50, 50, 25, 25); // Создаём кнопку
	auto* foregroundView = button.get(); // Окошко перед пользователем
	root->addSubview(std::move(button)); // Встраиваем кнопку в основное окошко
	foregroundView->handleClick(56, 70); // Кликаем в кнопку
	foregroundView->handleClick(160, 130); // Кликаем мимо кнопки
	
	std::wcout << "\n";
	return 0;
}
