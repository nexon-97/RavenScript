#include "ExpressionTestSuite.hpp"
#include "fsm/TerminalState.hpp"
#include "ExpressionTestCase.hpp"
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
	RegisterTestCase(std::make_shared<ExpressionTestCase>("1", "somevar = 25", m_stateMachine));
	RegisterTestCase(std::make_shared<ExpressionTestCase>("2", "a.b = c", m_stateMachine));
	RegisterTestCase(std::make_shared<ExpressionTestCase>("3", "5 = c", m_stateMachine));
	RegisterTestCase(std::make_shared<ExpressionTestCase>("4", "a.5", m_stateMachine));
	RegisterTestCase(std::make_shared<ExpressionTestCase>("5", "(a)", m_stateMachine));
	RegisterTestCase(std::make_shared<ExpressionTestCase>("6", "(foo = bar.(nest))", m_stateMachine));
	RegisterTestCase(std::make_shared<ExpressionTestCase>("7", "func(25, a)", m_stateMachine));
	RegisterTestCase(std::make_shared<ExpressionTestCase>("8", "func(a, bar(b), c)", m_stateMachine));
	RegisterTestCase(std::make_shared<ExpressionTestCase>("9", "foo = bar()", m_stateMachine));
	RegisterTestCase(std::make_shared<ExpressionTestCase>("10", "foo.a = self.bar(foo.b)", m_stateMachine));
}

}
}
