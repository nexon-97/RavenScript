#pragma once
#include <memory>
#include <string>
#include <vector>
#include "LexicalToken.hpp"
#include "ast/Node.hpp"
#include "StateId.hpp"

namespace ravenscript
{
namespace fsm
{

class State;
using StatePtr = std::shared_ptr<State>;

class State
{
public:
	State();
	State(State& state);
	virtual ~State();

	virtual StatePtr Clone() = 0;

	void SetId(StateId id) { m_id = id; }
	virtual StateId GetId() const { return m_id; }

	virtual ast::NodePtr Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode) = 0;
	virtual bool IsAvailable(LexicalToken*& istream, LexicalToken* end) = 0;

	void SetName(const std::string& name) { m_name = name; }
	const std::string& GetName() const { return m_name; }

protected:
	StateId m_id = StateId::None;
	std::string m_name;
};

}
}
