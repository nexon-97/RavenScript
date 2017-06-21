#pragma once
#include "Stack.hpp"
#include "Blob.hpp"
#include "fsm/StateMachine.hpp"
#include "fsm/ProductionId.hpp"

namespace ravenscript
{

class Interpreter
{
public:
	Interpreter();
	virtual ~Interpreter();

	int DoFile(const char* path);
	int LoadModule(const char* path);

protected:
	void InitProductions();

protected:
	Stack m_stack;
	fsm::StateMachinePtr m_productions[ProductionId::Count];
};

}
