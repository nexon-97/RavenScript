#pragma once
#include "LexicalTokenizer.hpp"

#include <iostream>

namespace ravenscript
{

bool LexicalTokenizer::Parse(char* textBlob, std::vector<LexicalToken>* tokensList)
{
	char* currentToken = textBlob;
	int tokenLength = 0;
	auto currentGroup = LexicalToken::SymbolGroup::Undefined;
		
	auto resetCurrentToken = [&tokenLength](char* currentSymbol, char** currentToken)
	{
		*currentToken = currentSymbol;
		tokenLength = 0;
	};

	auto saveCurrentToken = [&currentToken, &tokenLength, &tokensList]()
	{
		if (tokenLength > 0)
		{
			tokensList->emplace_back(currentToken, tokenLength, LexicalToken::TokenType::Identifier);
		}
	};

	resetCurrentToken(textBlob, &currentToken);

	while (*textBlob)
	{
		auto group = LexicalToken::GetSymbolGroup(*textBlob);

		if (group == LexicalToken::SymbolGroup::Undefined)
		{
			// Print symbol error & return empty tokens list
			std::cerr << "Undefined symbol: " << static_cast<int>(*textBlob) << std::endl;
			return false;
		}

		if (group != currentGroup)
		{
			// Write only non-empty tokens to the result list
			saveCurrentToken();
			resetCurrentToken(textBlob, &currentToken);
			currentGroup = group;
		}

		// Don't write space tokens
		if (group != LexicalToken::SymbolGroup::Space)
		{
			tokenLength++;
		}

		textBlob++;
	}

	// Save last token, accumulated after text processing
	saveCurrentToken();

	return true;
}

}
