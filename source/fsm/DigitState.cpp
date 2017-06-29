#include "DigitState.hpp"

namespace ravenscript
{
namespace fsm
{

bool DigitState::Parse(LexicalToken*& istream, LexicalToken* end)
{
	istream++;
	return true;
}

bool DigitState::IsAvailable(LexicalToken*& istream, LexicalToken* end)
{
	return istream->GetType() == LexicalToken::TokenType::Digit;
}

}
}
