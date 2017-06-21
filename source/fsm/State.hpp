#pragma once
#include <memory>
#include "LexicalToken.hpp"

namespace ravenscript
{
namespace fsm
{

class State
{
public:
	State();
	virtual ~State();

	virtual bool Match(LexicalToken* token) = 0;

	virtual void OnEnter() {}
	virtual void OnExit() {}
};

using StatePtr = std::shared_ptr<State>;

}
}
