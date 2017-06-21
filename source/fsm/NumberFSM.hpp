#pragma once
#include "StateMachine.hpp"

namespace ravenscript
{

class NumberFSM : public fsm::StateMachine
{
public:
	virtual bool Match(LexicalToken* token);
};

}
