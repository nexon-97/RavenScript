#pragma once
#include "TestSuite.hpp"
#include "fsm/StateMachine.hpp"
#include <string>

namespace ravenscript
{
namespace test
{

class IdentifierTestSuite : public TestSuite
{
public:
	IdentifierTestSuite();

	fsm::StateMachinePtr GetStateMachine() const { return m_stateMachine; }

protected:
	fsm::StateMachinePtr m_stateMachine;
};

}
}
