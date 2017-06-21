#pragma once
#include "State.hpp"

namespace ravenscript
{

class ConstantState : public fsm::State
{
public:
	explicit ConstantState(char* constant) 
		: m_constant(constant)
	{}

	virtual bool Match(LexicalToken* token);

private:
	char* m_constant = nullptr;
};

}
