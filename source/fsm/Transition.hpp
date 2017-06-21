#pragma once
#include "State.hpp"

namespace ravenscript
{
namespace fsm
{

struct Transition
{
public:
	explicit Transition(const StatePtr& from, const StatePtr& to)
		: m_from(from)
		, m_to(to)
	{}
	~Transition() = default;

protected:
	StatePtr m_from;
	StatePtr m_to;
};

using TransitionPtr = std::shared_ptr<Transition>;

}
}
