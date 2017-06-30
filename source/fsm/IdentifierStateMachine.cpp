#include "IdentifierStateMachine.hpp"
#include <algorithm>
#include <iterator>
#include "ast/IdentifierNode.hpp"

namespace ravenscript
{
namespace fsm
{

IdenitifierStateMachine::IdenitifierStateMachine()
	: StateMachine()
{

}

ast::NodePtr IdenitifierStateMachine::Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode)
{
	// Reset fsm state to entry
	SetCurrentState(m_entryState);

	// Enter recursion
	auto output = DoStep(istream, end, inputNode);

	if (!!output)
	{
		// Construct identifier value
		std::string idenitiferValue;
		for (const auto& part : m_identifierParts)
		{
			idenitiferValue += part->GetValue();
		}

		auto identifierNode = std::make_shared<ast::IdentifierNode>(idenitiferValue);
		return identifierNode;
	}

	return ast::NodePtr();
}

ast::NodePtr IdenitifierStateMachine::DoStep(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode)
{
	/// [TODO] Split state machine step into intependent phases

	std::vector<StatePtr> validStates;
	auto validStateFilter = [&istream, end](const StatePtr& state)
	{
		return state->IsAvailable(istream, end);
	};

	std::copy_if(m_possibleStates.begin(), m_possibleStates.end(), std::back_inserter(validStates), validStateFilter);

	ast::NodePtr parseResult;
	for (const StatePtr& state : validStates)
	{
		SetCurrentState(state);

		parseResult = state->Parse(istream, end, inputNode);
		auto literalNode = std::dynamic_pointer_cast<ast::LiteralNode>(parseResult);
		if (!!literalNode)
		{
			m_identifierParts.push_back(literalNode);
			return DoStep(istream, end, parseResult);
		}
	}

	if (!parseResult)
	{
		bool canTransitToFinalState = std::find(m_possibleStates.begin(), m_possibleStates.end(), m_finalState) != m_possibleStates.end();
		if (canTransitToFinalState)
		{
			parseResult = inputNode;
		}
	}

	return parseResult;
}

}
}
