#include "IdentifierTestSuite.hpp"
#include "fsm/TerminalState.hpp"
#include "TokenTestCase.hpp"
#include <set>
#include <ostream>

namespace ravenscript
{
namespace test
{

IdentifierTestSuite::IdentifierTestSuite()
{
	using namespace ravenscript::fsm;

	std::set<char> digits = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	std::set<char> letters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_' };

	m_stateMachine = std::make_shared<StateMachine>();
	auto startState = m_stateMachine->GetEntryState();
	auto finalState = m_stateMachine->GetFinalState();

	auto letterState = std::make_shared<TerminalState>(letters);
	auto digitState = std::make_shared<TerminalState>(digits);
	m_stateMachine->AddState(letterState);
	m_stateMachine->AddState(digitState);

	m_stateMachine->AddTransition(startState, letterState);
	m_stateMachine->AddTransition(letterState, digitState);
	m_stateMachine->AddTransition(digitState, letterState);
	m_stateMachine->AddTransition(letterState, finalState);
	m_stateMachine->AddTransition(digitState, finalState);
	m_stateMachine->AddTransition(letterState, letterState);
	m_stateMachine->AddTransition(digitState, digitState);

	// Register test cases
	RegisterTestCase(std::make_shared<TokenTestCase>("1", "_lol25kek", m_stateMachine));
	RegisterTestCase(std::make_shared<TokenTestCase>("2", "25kek", m_stateMachine));
}

}
}
