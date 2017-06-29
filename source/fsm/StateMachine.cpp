#include "StateMachine.hpp"
#include "EmptyState.hpp"
#include <algorithm>
#include <iterator>
#include <functional>

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

void StateMachine::AddTransition(const StatePtr& from, const StatePtr& to, int priority)
{
	m_transitions.push_back(std::make_shared<Transition>(from, to, priority));
}

bool StateMachine::Parse(LexicalToken*& istream, LexicalToken* end)
{
	// Reset fsm state to entry
	SetCurrentState(m_entryState);

	// Enter recursion
	DoStep(istream, end);

	return std::find(m_possibleStates.begin(), m_possibleStates.end(), m_finalState) != m_possibleStates.end();
}

void StateMachine::DoStep(LexicalToken*& istream, LexicalToken* end)
{
	std::vector<StatePtr> validStates;
	auto validStateFilter = [&istream, end](const StatePtr& state)
	{
		return state->IsAvailable(istream, end);
	};

	std::copy_if(m_possibleStates.begin(), m_possibleStates.end(), std::back_inserter(validStates), validStateFilter);

	for (const StatePtr& state : validStates)
	{
		SetCurrentState(state);

		if (state->Parse(istream, end))
		{
			DoStep(istream, end);
		}
	}
}

bool StateMachine::IsAvailable(LexicalToken*& istream, LexicalToken* end)
{
	auto pred = [&istream, end](const StatePtr& state)
	{
		return state->IsAvailable(istream, end);
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
	auto priorityComparator = [](const TransitionPtr& lhs, const TransitionPtr& rhs)
	{
		return lhs->GetPriority() > rhs->GetPriority();
	};
	std::sort(validTransitions.begin(), validTransitions.end(), priorityComparator);

	// Fill destination states vector
	for (const TransitionPtr& transition : validTransitions)
	{
		m_possibleStates.push_back(transition->GetDestinationState());
	}
}

}
}
