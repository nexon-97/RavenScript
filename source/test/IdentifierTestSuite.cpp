#include "IdentifierTestSuite.hpp"
#include "fsm/TerminalState.hpp"
#include "TokenTestCase.hpp"
#include "fsm/StateMachineConstructor.hpp"
#include <set>
#include <ostream>

namespace ravenscript
{
namespace test
{

IdentifierTestSuite::IdentifierTestSuite()
{
	auto constructor = fsm::StateMachineConstructor();
	m_stateMachine = constructor.ConstructIdentifierFSM();

	// Register test cases
	RegisterTestCase(std::make_shared<TokenTestCase>("1", "_lol25kek", m_stateMachine));
	RegisterTestCase(std::make_shared<TokenTestCase>("2", "25kek", m_stateMachine));
}

}
}
