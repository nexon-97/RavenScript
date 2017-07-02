#include "RecursiveState.hpp"

namespace ravenscript
{
namespace fsm
{

RecursiveState::RecursiveState(State* originalState)
	: m_originalState(originalState)
{
}

ast::NodePtr RecursiveState::Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode)
{
	return m_originalState->Parse(istream, end, inputNode);
}

bool RecursiveState::IsAvailable(LexicalToken*& istream, LexicalToken* end)
{
	return m_originalState->IsAvailable(istream, end);
}

StatePtr RecursiveState::Clone()
{
	return m_originalState->Clone();
}

}
}
