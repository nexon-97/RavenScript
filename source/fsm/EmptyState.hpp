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

	virtual bool Parse(char** istream) override;
	virtual bool IsAvailable(char* istream) override;
};

}
}
