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
	Init();
}

void StateMachine::Init()
{
	m_entryState = std::make_shared<EmptyState>();
	m_finalState = std::make_shared<EmptyState>();

	AddState(m_entryState);
	AddState(m_finalState);
}

StateMachine::StateMachine(StateMachine& stateMachine)
{
	SetName(stateMachine.GetName());

	// Copy transitions
	std::vector<std::pair<StatePtr, StatePtr>> uniqueOriginalStates;
	auto addUnique = [&uniqueOriginalStates](const StatePtr& state) -> StatePtr
	{
		auto duplicateFinder = [state](const std::pair<StatePtr, StatePtr>& pair)
		{
			return pair.first == state;
		};

		auto it = std::find_if(uniqueOriginalStates.begin(), uniqueOriginalStates.end(), duplicateFinder);
		if (it == uniqueOriginalStates.end())
		{
			auto clone = state->Clone();
			uniqueOriginalStates.push_back(std::make_pair(state, clone));
			return clone;
		}
		else
		{
			return it->second;
		}
	};

	for (const auto& transition : stateMachine.m_transitions)
	{
		auto srcState = transition->GetSourceState();
		auto destState = transition->GetDestinationState();

		auto srcCopy = addUnique(srcState);
		auto destCopy = addUnique(destState);

		m_transitions.push_back(std::make_shared<Transition>(srcCopy, destCopy, transition->GetPriority()));
	}

	// Add all states to database
	for (const auto& state : uniqueOriginalStates)
	{
		m_states.push_back(state.second);
	}

	// Find start & final states among the unique states
	auto particularStateFinder = [&uniqueOriginalStates](const StatePtr& state)
	{
		auto it = std::find_if(uniqueOriginalStates.begin(), uniqueOriginalStates.end(),
			[state](std::pair<StatePtr, StatePtr> pair) { return pair.first == state; });

		return it->second;
	};

	m_entryState = particularStateFinder(stateMachine.GetEntryState());
	m_finalState = particularStateFinder(stateMachine.GetFinalState());
}

StateMachine::~StateMachine()
{

}

StatePtr StateMachine::Clone()
{
	return StatePtr(new StateMachine(*this));
}

void StateMachine::AddState(const StatePtr& state)
{
	m_states.push_back(state);
}

void StateMachine::AddTransition(const StatePtr& from, const StatePtr& to, int priority)
{
	m_transitions.push_back(std::make_shared<Transition>(from, to, priority));
}

ast::NodePtr StateMachine::Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode)
{
	// Reset fsm state to entry
	SetCurrentState(m_entryState);

	// Enter recursion
	return DoStep(istream, end, inputNode);
}

ast::NodePtr StateMachine::DoStep(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode)
{
	auto restoreState = m_currentState;

	std::vector<StatePtr> validStates;
	ConstructValidStates(validStates, istream, end);

	ast::NodePtr parseResult;
	for (const StatePtr& state : validStates)
	{
		LexicalToken* streamOffset = istream;
		SetCurrentState(state);

		parseResult = state->Parse(istream, end, inputNode);
		if (!!parseResult)
		{
			SetCurrentState(state);
			auto stepResult = DoStep(istream, end, parseResult);
			if (!!stepResult)
			{
				return stepResult;
			}
			else
			{
				istream = streamOffset;
				continue;
			}
		}
		else
		{
			istream = streamOffset;
		}
	}

	if (!parseResult)
	{
		bool canTransitToFinalState = std::find(m_possibleStates.begin(), m_possibleStates.end(), m_finalState) != m_possibleStates.end();
		if (canTransitToFinalState)
		{
			parseResult = inputNode;
		}
	}

	SetCurrentState(restoreState);
	return parseResult;
}

bool StateMachine::IsAvailable(LexicalToken*& istream, LexicalToken* end)
{
	// Temporary set entry state to test fsm for availability
	auto currentState = m_currentState;
	SetCurrentState(m_entryState);

	// Find any valid transition from possible states
	auto pred = [&istream, end](const StatePtr& state)
	{
		return state->IsAvailable(istream, end);
	};
	auto it = std::find_if(m_possibleStates.begin(), m_possibleStates.end(), pred);
	bool result = it != m_possibleStates.end();

	// Restore current state
	SetCurrentState(currentState);

	return result;
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

void StateMachine::ConstructValidStates(std::vector<StatePtr>& validStates, LexicalToken*& istream, LexicalToken* end)
{
	// Leave empty valid states list, if stream has ended
	if (istream == end)
		return;

	auto validStateFilter = [&istream, end](const StatePtr& state)
	{
		return state->IsAvailable(istream, end);
	};

	std::copy_if(m_possibleStates.begin(), m_possibleStates.end(), std::back_inserter(validStates), validStateFilter);
}

}
}
