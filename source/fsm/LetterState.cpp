#include "LetterState.hpp"

namespace ravenscript
{
namespace fsm
{

bool LetterState::Parse(LexicalToken*& istream, LexicalToken* end)
{
	istream++;
	return true;
}

bool LetterState::IsAvailable(LexicalToken*& istream, LexicalToken* end)
{
	return istream->GetType() == LexicalToken::TokenType::Letter;
}

}
}
