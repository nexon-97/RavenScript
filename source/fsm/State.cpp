#include "State.hpp"

namespace ravenscript
{
namespace fsm
{

State::State()
{

}

State::State(State& state)
{
	m_name = state.GetName();
}

State::~State()
{

}

}
}
