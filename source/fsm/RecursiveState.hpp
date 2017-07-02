#pragma once
#include "State.hpp"

namespace ravenscript
{
namespace fsm
{

class RecursiveState : public State
{
public:
	explicit RecursiveState(State* originalState);
	virtual ~RecursiveState() = default;

	virtual StatePtr Clone() override;

	virtual ast::NodePtr Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode) override;
	virtual bool IsAvailable(LexicalToken*& istream, LexicalToken* end) override;

private:
	State* m_originalState;
};

}
}
