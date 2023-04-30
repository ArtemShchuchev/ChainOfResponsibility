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

Handler::Handler(std::unique_ptr<Handler> handler) : nextHandler_(std::move(handler))
{
}

void Handler::setNextHandler(std::unique_ptr<Handler> handler)
{
	nextHandler_ = std::move(handler);
}

Handler* Handler::getNextHandler()
{
	return nextHandler_.get();
}

Warning::Warning(std::unique_ptr<Handler> nextHandler)
{
	if (nextHandler) setNextHandler(std::move(nextHandler));
}

void Warning::handleLogMessage(LogMessage logMes)
{
	if (logMes.type() == ErrType::WARNING)
	{
		std::wcout << ansi2wide(logMes.message()) << "\n";
	}
	else getNextHandler()->handleLogMessage(logMes);
}

Error::Error(const std::string& filePath, std::unique_ptr<Handler> nextHandler) : filePath_(filePath)
{
	if (nextHandler) setNextHandler(std::move(nextHandler));
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

FatalError::FatalError(std::unique_ptr<Handler> nextHandler)
{
	if (nextHandler) setNextHandler(std::move(nextHandler));
}

void FatalError::handleLogMessage(LogMessage logMes)
{
	if (logMes.type() == ErrType::FATAL)
	{
		throw std::runtime_error(logMes.message());
	}
	else getNextHandler()->handleLogMessage(logMes);
}

UnknowError::UnknowError(std::unique_ptr<Handler> nextHandler)
{
	if (nextHandler) setNextHandler(std::move(nextHandler));
}

void UnknowError::handleLogMessage(LogMessage logMes)
{
	if (logMes.type() == ErrType::UNKNOW)
	{
		throw std::runtime_error(logMes.message());
	}
	else getNextHandler()->handleLogMessage(logMes);
}
