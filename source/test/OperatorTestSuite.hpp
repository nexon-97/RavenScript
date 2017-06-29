#pragma once
#include "TestSuite.hpp"
#include "fsm/StateMachine.hpp"
#include <string>

namespace ravenscript
{
namespace test
{

class OperatorTestSuite : public TestSuite
{
public:
	OperatorTestSuite();

protected:
	fsm::StateMachinePtr m_stateMachine;
};

}
}
