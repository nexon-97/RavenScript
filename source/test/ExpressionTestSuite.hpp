#pragma once
#include "TestSuite.hpp"
#include "fsm/StateMachine.hpp"
#include <string>

namespace ravenscript
{
namespace test
{

class ExpressionTestSuite : public TestSuite
{
public:
	ExpressionTestSuite();

protected:
	fsm::StateMachinePtr m_stateMachine;
};

}
}
