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

bool TerminalState::Parse(char** istream)
{
	(*istream)++;
	return true;
}

bool TerminalState::IsAvailable(char* istream)
{
	return m_availableSymbols.find(*istream) != m_availableSymbols.end();
}

}
}
