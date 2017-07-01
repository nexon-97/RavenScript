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

	virtual StatePtr Clone() override;

	virtual ast::NodePtr Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode) override;
	virtual bool IsAvailable(LexicalToken*& istream, LexicalToken* end) override;

protected:
	std::set<char> m_availableSymbols;
};

}
}
