#pragma once
#include "Interpreter.hpp"
#include "LexicalTokenizer.hpp"

#include <fstream>
#include <iostream>

namespace ravenscript
{

Interpreter::Interpreter()
{

}

Interpreter::~Interpreter()
{

}

int Interpreter::DoFile(const char* filepath)
{
	char* fileBlob = LoadFile(filepath);
	if (!!fileBlob)
	{
		LexicalTokenizer lexicalTokenizer;
		std::vector<LexicalToken> lexicalTokens;
		if (!lexicalTokenizer.Parse(fileBlob, &lexicalTokens))
		{
			std::cerr << "Failed to parse file \"" << filepath << "\"!" << std::endl;
			return 1;
		}

		std::cout << "File \"" << filepath << "\" parsed lexically!" << std::endl;
		
		std::cout << "[Tokens]" << std::endl;
		for (auto item : lexicalTokens)
		{
			std::cout << '[' << item.GetValue() << "] ";
		}
		std::cout << std::endl;

		delete[] fileBlob;
		return 0;
	}

	std::cerr << "Failed to execute file \"" << filepath << "\"!" << std::endl;
	return 1;
}

int Interpreter::LoadModule(const char* path)
{
	return 0;
}

char* Interpreter::LoadFile(const char* path) const
{
	std::ifstream fs;
	fs.open(path, std::ios_base::in | std::ios_base::binary);
	if (fs.is_open())
	{
		fs.seekg(0, std::ios_base::end);
		std::size_t fileSize = fs.tellg();
		fs.seekg(0, std::ios_base::beg);

		char* buffer = new char[fileSize + 1];
		fs.read(buffer, fileSize);
		buffer[fileSize] = '\0';

		fs.close();

		return buffer;
	}

	return nullptr;
}

}
