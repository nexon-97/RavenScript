#include "TerminalState.hpp"
#include "ast/StringLiteralNode.hpp"

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

ast::NodePtr TerminalState::Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode)
{
	auto output = std::make_shared<ast::StringLiteralNode>(istream->GetValue());
	istream++;

	return output;
}

bool TerminalState::IsAvailable(LexicalToken*& istream, LexicalToken* end)
{
	int length = strlen(istream->GetValue());
	return length == 1;
}

}
}
