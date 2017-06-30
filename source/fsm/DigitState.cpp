#include "DigitState.hpp"
#include "ast/IntegerLiteralNode.hpp"

namespace ravenscript
{
namespace fsm
{

ast::NodePtr DigitState::Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode)
{
	int value = 0;

	try
	{
		value = std::stoi(std::string(istream->GetValue()));
	}
	catch (std::exception&)
	{
		return ast::NodePtr();
	}

	auto output = std::make_shared<ast::IntegerLiteralNode>(value);
	istream++;

	return output;
}

bool DigitState::IsAvailable(LexicalToken*& istream, LexicalToken* end)
{
	return istream->GetType() == LexicalToken::TokenType::Digit;
}

}
}
