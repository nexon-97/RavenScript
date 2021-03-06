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
	StateMachine(StateMachine& stateMachine);
	virtual ~StateMachine();

	virtual StatePtr Clone() override;

	void AddState(const StatePtr& state);
	void AddTransition(const StatePtr& from, const StatePtr& to, int priority);

	StatePtr GetEntryState() const { return m_entryState; }
	StatePtr GetFinalState() const { return m_finalState; }

	virtual ast::NodePtr Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode) override;
	virtual bool IsAvailable(LexicalToken*& istream, LexicalToken* end) override;

protected:
	virtual void SetCurrentState(const StatePtr& state);
	virtual ast::NodePtr DoStep(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode);

	void Init();
	void UpdatePossibleStates();
	void ConstructValidStates(std::vector<StatePtr>& validStates, LexicalToken*& istream, LexicalToken* end);

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
