#pragma once
#include "State.hpp"
#include <set>

namespace ravenscript
{
namespace fsm
{

class TerminalState : public State
{
public:
	explicit TerminalState(const std::set<char>& symbols);
	virtual ~TerminalState();

	virtual bool Parse(char** istream) override;
	virtual bool IsAvailable(char* istream) override;

protected:
	std::set<char> m_availableSymbols;
};

}
}
