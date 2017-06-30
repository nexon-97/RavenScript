#pragma once
#include "State.hpp"

namespace ravenscript
{
namespace fsm
{

class DigitState : public State
{
public:
	virtual ast::NodePtr Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode) override;
	virtual bool IsAvailable(LexicalToken*& istream, LexicalToken* end) override;
};

}
}
