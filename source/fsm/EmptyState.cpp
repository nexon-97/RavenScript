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

bool EmptyState::Parse(char** istream)
{
	return false;
}

bool EmptyState::IsAvailable(char* istream)
{
	return false;
}

}
}
