#include "ChainOfResponsibility.h"

LogMessage::LogMessage(std::unique_ptr<LogMessage> handler, const std::string& message) : message_(message)
{
	handler->nextHandler = this;
	handler_v.push_back(std::move(handler));
}

const std::string& LogMessage::message() const
{
	return message_;
}

Warning::Warning(const std::string& message) : LogMessage(*this, message)
{
}

void Warning::logMessage()
{
	std::wcout << utf2wide(message()) << "\n";
}

Error::Error(const std::string& filePath) : filePath_(filePath), LogMessage(*this)
{
}

void Error::logMessage()
{
	std::ofstream fout;
	fout.open(filePath_, std::ios_base::app);
	if (fout.is_open()) fout << message() << std::endl;
}

FatalError::FatalError() : LogMessage(*this)
{
}

void FatalError::logMessage()
{
	throw std::runtime_error(message());
}

UnknowError::UnknowError() : LogMessage(*this)
{
}

void UnknowError::logMessage()
{
	throw std::runtime_error(message());
}
