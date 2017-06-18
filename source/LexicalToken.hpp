#pragma once
#include "Blob.hpp"

#include <memory>
#include <map>

namespace ravenscript
{

class LexicalToken
{
public:
	enum class TokenType
	{
		Identifier,
		Number,
		Operator
	};

	enum class SymbolGroup
	{
		Letter,
		Digit,
		Space,
		Sign,
		Brace,
		EndOfFile,
		Undefined,
	};

public:
	explicit LexicalToken(char* value, int size, TokenType type);
	~LexicalToken() = default;

	char* GetValue() const { return m_value->data; }
	TokenType GetType() const { return m_type; }

	static SymbolGroup GetSymbolGroup(char symbol);

private:
	static std::map<char, SymbolGroup> s_symbolGroupMapping;

private:
	std::shared_ptr<Blob> m_value;
	TokenType m_type;
};

}
