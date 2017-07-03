#pragma once
#include "StateMachine.hpp"
#include "ast/LiteralNode.hpp"

namespace ravenscript
{
namespace fsm
{

class FunctionCallState : public StateMachine
{
public:
	FunctionCallState();
	virtual ~FunctionCallState() = default;

	virtual StatePtr Clone() override;

	virtual ast::NodePtr Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode) override;

protected:
	enum ParsingPhase : int
	{
		FunctionId,
		BraceOpen,
		Expression,
		Comma,
		BraceClose,
		Finished
	};

	struct FunctionCallData
	{
		ast::NodePtr name;
		std::vector<ast::NodePtr> params;
	};

	virtual ast::NodePtr DoStep(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode);

	ParsingPhase GetNextPhase(ParsingPhase currentPhase)
	{
		if (currentPhase != ParsingPhase::Finished)
		{
			return static_cast<ParsingPhase>(currentPhase + 1);
		}

		return ParsingPhase::Finished;
	}

protected:
	ParsingPhase* m_parsingPhase;
	FunctionCallData* m_callData;
};

using StateMachinePtr = std::shared_ptr<StateMachine>;

}
}
