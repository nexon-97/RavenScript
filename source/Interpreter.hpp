#pragma once
#include "Stack.hpp"
#include "Blob.hpp"
#include "fsm/StateMachine.hpp"

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
};

}
