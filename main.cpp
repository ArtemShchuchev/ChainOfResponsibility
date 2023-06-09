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

	auto handler = std::make_unique<Warning>
		(std::make_unique<Error>
			("error.txt", std::make_unique<FatalError>
				(std::make_unique<UnknowError>() )));

	handler->handleLogMessage({ ErrType::WARNING, "Предупреждение!" });
	handler->handleLogMessage({ ErrType::ERR, "Ошибка!" });
	try
	{
		handler->handleLogMessage({ ErrType::FATAL, "Всё совсем плохо!" });
	}
	catch (const std::exception& err)
	{
		std::wcerr << L"Исключение: " << ansi2wide(err.what()) << "\n";
	}
	try
	{
		handler->handleLogMessage({ ErrType::UNKNOW, "НИпонятно чО!" });
	}
	catch (const std::exception& err)
	{
		std::wcerr << L"Исключение: " << ansi2wide(err.what()) << "\n";
	}
	
	std::wcout << "\n";
	return 0;
}
