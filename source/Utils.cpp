#include "Utils.hpp"

#include <fstream>

namespace ravenscript
{
namespace utils
{

BlobPtr LoadFile(const char* path)
{
	std::ifstream fs;
	fs.open(path, std::ios_base::in | std::ios_base::binary);
	if (fs.is_open())
	{
		fs.seekg(0, std::ios_base::end);
		std::size_t fileSize = static_cast<std::size_t>(fs.tellg());
		fs.seekg(0, std::ios_base::beg);

		std::size_t bufferSize = fileSize + 1;
		auto buffer = std::make_shared<Blob>(new char[bufferSize], bufferSize);
		fs.read(buffer->data, fileSize);
		buffer->data[fileSize] = '\0';

		fs.close();

		return buffer;
	}

	return nullptr;
}

std::shared_ptr<tinyxml2::XMLDocument> LoadXmlFile(const char* path)
{
	auto modelDocument = std::make_shared<tinyxml2::XMLDocument>();
	if (modelDocument->LoadFile(path) == tinyxml2::XML_SUCCESS)
	{
		return modelDocument;
	}

	// Return nullptr in case of error
	return nullptr;
}

std::string ValueOrEmpty(const char* str)
{
	return (!!str) ? std::string(str) : std::string();
}

Operator CharToOperator(char c)
{
	switch (c)
	{
		case '=':
			return Operator::Assignment;
		case '.':
			return Operator::Index;
		case '+':
			return Operator::Add;
		case '-':
			return Operator::Subtract;
		case '*':
			return Operator::Multiply;
		case '/':
			return Operator::Divide;
		case '%':
			return Operator::Mod;
	}

	return Operator::Undefined;
}

}
}
