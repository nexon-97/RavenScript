#include "EmptyState.hpp"

namespace ravenscript
{
namespace fsm
{

EmptyState::EmptyState()
{

}

EmptyState::~EmptyState()
{

}

ast::NodePtr EmptyState::Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode)
{
	return false;
}

bool EmptyState::IsAvailable(LexicalToken*& istream, LexicalToken* end)
{
	return false;
}

StatePtr EmptyState::Clone()
{
	return StatePtr(new EmptyState(*this));
}

}
}
