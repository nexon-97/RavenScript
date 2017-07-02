#pragma once
#include "State.hpp"
#include "Operator.hpp"

namespace ravenscript
{
namespace fsm
{

class OperatorState : public State
{
public:
	explicit OperatorState(Operator op) : m_operator(op) {}

	virtual StatePtr Clone() override;

	virtual ast::NodePtr Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode) override;
	virtual bool IsAvailable(LexicalToken*& istream, LexicalToken* end) override;

private:
	Operator m_operator;
};

}
}
