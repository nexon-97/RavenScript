#pragma once
#include <memory>
#include <string>
#include <vector>
#include "LexicalToken.hpp"
#include "ast/Node.hpp"

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

	virtual ast::NodePtr Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode) = 0;
	virtual bool IsAvailable(LexicalToken*& istream, LexicalToken* end) = 0;

	void SetName(const std::string& name) { m_name = name; }
	const std::string& GetName() const { return m_name; }

protected:
	std::string m_name;
};

}
}
