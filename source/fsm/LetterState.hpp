#pragma once
#include "State.hpp"

namespace ravenscript
{
namespace fsm
{

class LetterState : public State
{
public:
	virtual bool Parse(LexicalToken*& istream, LexicalToken* end) override;
	virtual bool IsAvailable(LexicalToken*& istream, LexicalToken* end) override;
};

}
}
