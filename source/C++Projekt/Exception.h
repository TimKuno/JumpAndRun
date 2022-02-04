#pragma once
#include <string>

class Exception
{
public:
	Exception();
	explicit Exception(const std::string& error_msg);
	~Exception();

	void set_error(std::string error_msg);
	std::string get_error() const;

private:
	std::string error_msg;
};

class FileNotFoundException : public Exception
{
public:
	FileNotFoundException();
	explicit FileNotFoundException(const std::string& error_msg);
	~FileNotFoundException();
};