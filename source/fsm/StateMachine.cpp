#include "StateMachine.hpp"
#include "EmptyState.hpp"
#include <algorithm>
#include <iterator>

namespace ravenscript
{
namespace fsm
{

StateMachine::StateMachine()
{
	m_entryState = std::make_shared<EmptyState>();
	m_finalState = std::make_shared<EmptyState>();

	AddState(m_entryState);
	AddState(m_finalState);
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

bool StateMachine::Parse(char** istream)
{
	// Reset fsm state to entry
	SetCurrentState(m_entryState);

	while (DoStep(istream));

	return std::find(m_possibleStates.begin(), m_possibleStates.end(), m_finalState) != m_possibleStates.end();
}

bool StateMachine::DoStep(char** istream)
{
	std::vector<StatePtr> validStates;
	auto validStateFilter = [istream](const StatePtr& state)
	{
		return state->IsAvailable(*istream);
	};

	std::copy_if(m_possibleStates.begin(), m_possibleStates.end(), std::back_inserter(validStates), validStateFilter);

	for (const StatePtr& state : validStates)
	{
		SetCurrentState(state);

		if (state->Parse(istream))
		{
			return true;
		}
	}

	return false;
}

bool StateMachine::IsAvailable(char* istream)
{
	auto pred = [istream](const StatePtr& state)
	{
		return state->IsAvailable(istream);
	};
	auto it = std::find_if(m_states.begin(), m_states.end(), pred);

	return it != m_states.end();
}

void StateMachine::SetCurrentState(const StatePtr& state)
{
	m_currentState = state;

	UpdatePossibleStates();
}

void StateMachine::UpdatePossibleStates()
{
	m_possibleStates.clear();

	// Filter transitions
	std::vector<TransitionPtr> validTransitions;
	auto validTransitionsFilter = [this](const TransitionPtr& transition)
	{
		return transition->GetSourceState() == m_currentState;
	};

	std::copy_if(m_transitions.begin(), m_transitions.end(), std::back_inserter(validTransitions), validTransitionsFilter);

	// Fill destination states vector
	for (const TransitionPtr& transition : validTransitions)
	{
		m_possibleStates.push_back(transition->GetDestinationState());
	}
}

}
}
