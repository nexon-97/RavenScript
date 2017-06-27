#pragma once
#include "State.hpp"
#include "Singleton.hpp"
#include <map>

namespace ravenscript
{
namespace fsm
{

class StateTypes : public Singleton<StateTypes>
{
public:
	StateTypes() = default;
	~StateTypes() = default;

	void Init();

protected:
	std::map<std::string, StatePtr> m_types;
};

}
}
