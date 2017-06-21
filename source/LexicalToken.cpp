#include "LexicalToken.hpp"

namespace ravenscript
{

std::map<char, LexicalToken::SymbolGroup> LexicalToken::s_symbolGroupMapping
{
	std::make_pair(' ', SymbolGroup::Space),
	std::make_pair('\t', SymbolGroup::Space),
	std::make_pair('\n', SymbolGroup::Space),
	std::make_pair('\r', SymbolGroup::Space),
	std::make_pair('"', SymbolGroup::Sign),
	std::make_pair('%', SymbolGroup::Sign),
	std::make_pair('\'', SymbolGroup::Sign),
	std::make_pair('(', SymbolGroup::Brace),
	std::make_pair(')', SymbolGroup::Brace),
	std::make_pair('*', SymbolGroup::Sign),
	std::make_pair('+', SymbolGroup::Sign),
	std::make_pair('-', SymbolGroup::Sign),
	std::make_pair('/', SymbolGroup::Sign),
	std::make_pair(',', SymbolGroup::Sign),
	std::make_pair('.', SymbolGroup::Sign),
	std::make_pair(';', SymbolGroup::Sign),
	std::make_pair('<', SymbolGroup::Sign),
	std::make_pair('>', SymbolGroup::Sign),
	std::make_pair('=', SymbolGroup::Sign),
	std::make_pair('[', SymbolGroup::Brace),
	std::make_pair(']', SymbolGroup::Brace),
	std::make_pair('{', SymbolGroup::Brace),
	std::make_pair('}', SymbolGroup::Brace),
	std::make_pair('0', SymbolGroup::Digit),
	std::make_pair('1', SymbolGroup::Digit),
	std::make_pair('2', SymbolGroup::Digit),
	std::make_pair('3', SymbolGroup::Digit),
	std::make_pair('4', SymbolGroup::Digit),
	std::make_pair('5', SymbolGroup::Digit),
	std::make_pair('6', SymbolGroup::Digit),
	std::make_pair('7', SymbolGroup::Digit),
	std::make_pair('8', SymbolGroup::Digit),
	std::make_pair('9', SymbolGroup::Digit),
	std::make_pair('$', SymbolGroup::Letter),
};


LexicalToken::LexicalToken(char* value, int size, TokenType type)
	: m_type(type)
{
	m_value.reset(new Blob(new char[size + 1], size + 1));
	strncpy_s(m_value->data, size + 1, value, size);
	m_value->data[size] = '\0';
}
	
LexicalToken::SymbolGroup LexicalToken::GetSymbolGroup(char symbol)
{
	auto it = s_symbolGroupMapping.find(symbol);
	if (it != s_symbolGroupMapping.end())
	{
		return it->second;
	}

	if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'))
	{
		return SymbolGroup::Letter;
	}

	return SymbolGroup::Undefined;
}

}
