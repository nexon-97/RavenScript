#pragma once
#include "State.hpp"

namespace ravenscript
{
namespace fsm
{

class EmptyState : public State
{
public:
	EmptyState();
	virtual ~EmptyState();

	virtual StatePtr Clone() override;

	virtual ast::NodePtr Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode) override;
	virtual bool IsAvailable(LexicalToken*& istream, LexicalToken* end) override;
};

}
}
