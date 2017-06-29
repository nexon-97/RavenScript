#include "OperatorTestSuite.hpp"
#include "fsm/TerminalState.hpp"
#include "OperatorTestCase.hpp"
#include "fsm/StateMachineConstructor.hpp"
#include <set>
#include <ostream>

namespace ravenscript
{
namespace test
{

OperatorTestSuite::OperatorTestSuite()
{
	auto constructor = fsm::StateMachineConstructor();
	m_stateMachine = constructor.ConstructOperatorFSM();

	// Register test cases
	RegisterTestCase(std::make_shared<OperatorTestCase>("Assignment", "=", m_stateMachine));
	RegisterTestCase(std::make_shared<OperatorTestCase>("Dot", ".", m_stateMachine));
	RegisterTestCase(std::make_shared<OperatorTestCase>("Mixed operator", ".=", m_stateMachine));
}

}
}
