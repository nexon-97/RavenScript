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

bool EmptyState::Parse(LexicalToken*& istream, LexicalToken* end)
{
	return false;
}

bool EmptyState::IsAvailable(LexicalToken*& istream, LexicalToken* end)
{
	return false;
}

}
}
