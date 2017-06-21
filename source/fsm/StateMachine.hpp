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

	bool Load(const char* path);

protected:
	std::vector<StatePtr> m_states;
	std::vector<TransitionPtr> m_transitions;
	LexicalToken* m_currentToken = nullptr;
};

using StateMachinePtr = std::shared_ptr<StateMachine>;

}
}
