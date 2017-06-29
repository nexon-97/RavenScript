#include "WordState.hpp"

namespace ravenscript
{
namespace fsm
{

WordState::WordState(const char* word)
	: m_word(word)
{
}

bool WordState::Parse(LexicalToken*& istream, LexicalToken* end)
{
	istream++;
	return true;
}

bool WordState::IsAvailable(LexicalToken*& istream, LexicalToken* end)
{
	return strcmp(istream->GetValue(), m_word) == 0;
}

}
}
