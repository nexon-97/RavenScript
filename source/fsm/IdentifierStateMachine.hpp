#pragma once
#include "StateMachine.hpp"
#include "ast/LiteralNode.hpp"

namespace ravenscript
{
namespace fsm
{

class IdenitifierStateMachine : public StateMachine
{
public:
	IdenitifierStateMachine();
	virtual ~IdenitifierStateMachine() = default;

	virtual ast::NodePtr Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode) override;

protected:
	virtual ast::NodePtr DoStep(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode);

protected:
	std::vector<ast::LiteralNodePtr> m_identifierParts;
};

using StateMachinePtr = std::shared_ptr<StateMachine>;

}
}
