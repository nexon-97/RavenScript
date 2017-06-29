#pragma once
#include "StateMachine.hpp"

namespace ravenscript
{
namespace fsm
{

class StateMachineConstructor
{
public:
	StateMachineConstructor() = default;
	~StateMachineConstructor() = default;

	StateMachinePtr ConstructIdentifierFSM();
	StateMachinePtr ConstructOperatorFSM();
	StateMachinePtr ConstructExpressionFSM();
};

}
}
