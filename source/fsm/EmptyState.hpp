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

	virtual bool Parse(LexicalToken*& istream, LexicalToken* end) override;
	virtual bool IsAvailable(LexicalToken*& istream, LexicalToken* end) override;
};

}
}
