#pragma once
#include "State.hpp"
#include "Transition.hpp"
#include "LexicalToken.hpp"

#include <vector>

namespace ravenscript
{
namespace fsm
{

class StateMachine : public State
{
public:
	StateMachine();
	virtual ~StateMachine();

	void AddState(const StatePtr& state);
	void AddTransition(const StatePtr& from, const StatePtr& to);

	StatePtr GetEntryState() const { return m_entryState; }
	StatePtr GetFinalState() const { return m_finalState; }

	virtual bool Parse(char** istream) override;
	virtual bool IsAvailable(char* istream) override;

protected:
	void SetCurrentState(const StatePtr& state);
	void UpdatePossibleStates();

	bool DoStep(char** istream);

protected:
	std::vector<StatePtr> m_states;
	std::vector<TransitionPtr> m_transitions;
	std::vector<StatePtr> m_possibleStates;
	StatePtr m_entryState;
	StatePtr m_finalState;
	StatePtr m_currentState;
};

using StateMachinePtr = std::shared_ptr<StateMachine>;

}
}
