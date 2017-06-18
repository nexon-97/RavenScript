#pragma once
#include "Stack.hpp"

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
	char* LoadFile(const char* path) const;

protected:
	Stack m_stack;
};

}
