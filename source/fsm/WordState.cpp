#include "WordState.hpp"
#include "ast/StringLiteralNode.hpp"

namespace ravenscript
{
namespace fsm
{

WordState::WordState(const char* word)
	: m_word(word)
{
}

ast::NodePtr WordState::Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode)
{
	auto output = std::make_shared<ast::StringLiteralNode>(istream->GetValue());
	istream++;

	return output;
}

bool WordState::IsAvailable(LexicalToken*& istream, LexicalToken* end)
{
	return strcmp(istream->GetValue(), m_word) == 0;
}

StatePtr WordState::Clone()
{
	return StatePtr(new WordState(*this));
}

}
}
