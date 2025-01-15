#include "ExceptionHandler.h"

ExceptionHandler::ExceptionHandler(enum class ErrorCode errorCode, string message)
{
	this->errorCode = errorCode;
	this->message = message;
}

enum class ErrorCode ExceptionHandler::GetErrorCode() const { return this->errorCode; }

string ExceptionHandler::GetErrorMessage() const { return this->message; }
