#pragma once
#include "Interpreter.hpp"
#include "LexicalTokenizer.hpp"
#include "fsm/NumberFSM.hpp"
#include "Utils.hpp"

#include <iostream>

namespace ravenscript
{

Interpreter::Interpreter()
{
	InitProductions();
}

Interpreter::~Interpreter()
{

}

int Interpreter::DoFile(const char* filepath)
{
	BlobPtr fileBlob = utils::LoadFile(filepath);
	if (!!fileBlob)
	{
		LexicalTokenizer lexicalTokenizer;
		std::vector<LexicalToken> lexicalTokens;
		if (!lexicalTokenizer.Parse(fileBlob->data, lexicalTokens))
		{
			std::cerr << "Failed to parse file \"" << filepath << "\"!" << std::endl;
			return 1;
		}

		std::cout << "[Tokens]" << std::endl;
		for (auto item : lexicalTokens)
		{
			std::cout << '[' << item.GetValue() << "] ";
		}
		std::cout << std::endl;

		return 0;
	}

	std::cerr << "Failed to execute file \"" << filepath << "\"!" << std::endl;
	return 1;
}

int Interpreter::LoadModule(const char* path)
{
	return 0;
}

void Interpreter::InitProductions()
{
	m_productions[ProductionId::Number].reset(new NumberFSM());
	auto& numberProduction = m_productions[ProductionId::Number];
}

}
