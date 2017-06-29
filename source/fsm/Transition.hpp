#pragma once
#include "State.hpp"

namespace ravenscript
{
namespace fsm
{

struct Transition
{
public:
	explicit Transition(const StatePtr& from, const StatePtr& to, int priority)
		: m_from(from)
		, m_to(to)
		, m_priority(priority)
	{}
	~Transition() = default;

	StatePtr GetSourceState() const { return m_from; }
	StatePtr GetDestinationState() const { return m_to; }
	int GetPriority() const { return m_priority; }

protected:
	StatePtr m_from;
	StatePtr m_to;
	int m_priority;
};

using TransitionPtr = std::shared_ptr<Transition>;

}
}
