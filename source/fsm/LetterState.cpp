#include "LetterState.hpp"
#include "ast/StringLiteralNode.hpp"

namespace ravenscript
{
namespace fsm
{

ast::NodePtr LetterState::Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode)
{
	auto output = std::make_shared<ast::StringLiteralNode>(istream->GetValue());
	istream++;

	return output;
}

bool LetterState::IsAvailable(LexicalToken*& istream, LexicalToken* end)
{
	return istream->GetType() == LexicalToken::TokenType::Letter;
}

}
}
