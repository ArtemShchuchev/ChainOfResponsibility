#include "ChainOfResponsibility.h"

LogMessage::LogMessage(ErrType errType, const std::string& message)
	: errType_(errType), message_(message)
{
}

ErrType LogMessage::type() const
{
	return errType_;
}

const std::string& LogMessage::message() const
{
	return message_;
}

Handler::Handler(Handler* handler) : nextHandler(handler)
{
}

void Handler::setNextHandler(Handler* handler)
{
	nextHandler = std::move(handler);
}

Handler* Handler::getNextHandler()
{
	return std::move(nextHandler);
}

Warning::Warning(Handler* nextHandler)
{
	if (nextHandler) setNextHandler(nextHandler);
}

void Warning::handleLogMessage(LogMessage logMes)
{
	if (logMes.type() == ErrType::WARNING)
	{
		std::wcout << ansi2wide(logMes.message()) << "\n";
	}
	else getNextHandler()->handleLogMessage(logMes);
}

Error::Error(const std::string& filePath, Handler* nextHandler) : filePath_(filePath)
{
	if (nextHandler) setNextHandler(nextHandler);
}

void Error::handleLogMessage(LogMessage logMes)
{
	if (logMes.type() == ErrType::ERR)
	{
		std::ofstream fout;
		fout.open(filePath_, std::ios_base::app);
		if (fout.is_open()) fout << logMes.message() << std::endl;
	}
	else getNextHandler()->handleLogMessage(logMes);
}

FatalError::FatalError(Handler* nextHandler)
{
	if (nextHandler) setNextHandler(nextHandler);
}

void FatalError::handleLogMessage(LogMessage logMes)
{
	if (logMes.type() == ErrType::FATAL)
	{
		throw std::runtime_error(logMes.message());
	}
	else getNextHandler()->handleLogMessage(logMes);
}

UnknowError::UnknowError(Handler* nextHandler)
{
	if (nextHandler) setNextHandler(nextHandler);
}

void UnknowError::handleLogMessage(LogMessage logMes)
{
	if (logMes.type() == ErrType::UNKNOW)
	{
		throw std::runtime_error(logMes.message());
	}
	else getNextHandler()->handleLogMessage(logMes);
}
