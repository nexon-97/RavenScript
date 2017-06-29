#include "TerminalState.hpp"

namespace ravenscript
{
namespace fsm
{

TerminalState::TerminalState(const std::set<char>& symbols)
	: m_availableSymbols(symbols)
{

}

TerminalState::~TerminalState()
{

}

bool TerminalState::Parse(LexicalToken*& istream, LexicalToken* end)
{
	//(*istream)++;
	return true;
}

bool TerminalState::IsAvailable(LexicalToken*& istream, LexicalToken* end)
{
	return false;
	//return m_availableSymbols.find(*istream) != m_availableSymbols.end();
}

}
}
