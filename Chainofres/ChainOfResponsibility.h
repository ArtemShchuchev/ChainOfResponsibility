#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "SecondaryFunction.h"

enum class ErrType{UNKNOW, WARNING, ERR, FATAL};

class LogMessage
{
private:
    std::string message_;
    ErrType errType_;
public:
    LogMessage(ErrType errType, const std::string& message);
    ErrType type() const;
    const std::string& message() const;
};

/*
    Каждый обработчик умеет:
    - обрабатывать сообщение только определённого типа,
    - передавать сообщение следующему обработчику.
*/
class Handler
{
private:
    Handler* nextHandler;
public:
    Handler(Handler* handler = nullptr);
    virtual void handleLogMessage(LogMessage logMes){}
    void setNextHandler(Handler* handler);
    Handler* getNextHandler();
};
/*
    Обработчик предупреждения должен напечатать сообщение в консоль.
*/
class Warning : public Handler
{
public:
    Warning(Handler* nextHandler = nullptr);
    void handleLogMessage(LogMessage logMes) override;
};

/*
    Обработчик обычной ошибки должен записать её в файл по указанному пути.
*/
class Error : public Handler
{
private:
    std::string filePath_;
public:
    Error(const std::string& filePath, Handler* nextHandler = nullptr);
    void handleLogMessage(LogMessage logMes) override;
};

/*
    Обработчик фатальной ошибки должен выбросить исключение с текстом сообщения,
    потому что предполагается, что программа должна прекратить выполнение
    после возникновения фатальной ошибки.
*/
class FatalError : public Handler
{
public:
    FatalError(Handler* nextHandler = nullptr);
    void handleLogMessage(LogMessage logMes) override;
};

/*
    Обработчик неизвестного сообщения должен выбросить исключение с текстом
	о необработанном сообщении.
*/
class UnknowError : public Handler
{
public:
    UnknowError(Handler* nextHandler = nullptr);
    void handleLogMessage(LogMessage logMes) override;
};
