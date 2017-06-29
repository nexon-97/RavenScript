#include "ExpressionTestSuite.hpp"
#include "fsm/TerminalState.hpp"
#include "TokenTestCase.hpp"
#include "fsm/StateMachineConstructor.hpp"
#include <set>
#include <ostream>

namespace ravenscript
{
namespace test
{

ExpressionTestSuite::ExpressionTestSuite()
{
	auto constructor = fsm::StateMachineConstructor();
	m_stateMachine = constructor.ConstructExpressionFSM();

	// Register test cases
	RegisterTestCase(std::make_shared<TokenTestCase>("1", "somevar = 25", m_stateMachine));
}

}
}
