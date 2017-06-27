#pragma once
#include <memory>

namespace ravenscript
{
namespace fsm
{

class State
{
public:
	State();
	virtual ~State();

	virtual bool Parse(char** istream) = 0;
	virtual bool IsAvailable(char* istream) = 0;
};

using StatePtr = std::shared_ptr<State>;

}
}
