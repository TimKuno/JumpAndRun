#include "Exception.h"
#include <utility>


void Exception::set_error(std::string error_msg)
{
	this->error_msg = std::move(error_msg);
}

std::string Exception::get_error() const
{
	return this->error_msg;
}


#pragma region

Exception::Exception()
{
	this->set_error("Ein Fehler ist aufgetreten.");
}

Exception::Exception(const std::string& error_msg)
{
	if (!error_msg.empty())
		this->set_error(error_msg);
}

Exception::~Exception()
= default;

#pragma endregion Default Exception

#pragma region

FileNotFoundException::FileNotFoundException()
{
	this->set_error("Eine Datei wurde nicht gefunden.");
}

FileNotFoundException::FileNotFoundException(const std::string& error_msg)
{
	if (!error_msg.empty())
		this->set_error(error_msg);
}

FileNotFoundException::~FileNotFoundException()
= default;

#pragma endregion FileException
