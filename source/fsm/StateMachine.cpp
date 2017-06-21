#include "StateMachine.hpp"

namespace ravenscript
{
namespace fsm
{

StateMachine::StateMachine()
{

}

StateMachine::~StateMachine()
{

}

void StateMachine::AddState(const StatePtr& state)
{
	m_states.push_back(state);
}

void StateMachine::AddTransition(const StatePtr& from, const StatePtr& to)
{
	m_transitions.push_back(std::make_shared<Transition>(from, to));
}

}
}
