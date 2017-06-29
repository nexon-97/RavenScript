#pragma once
#include "State.hpp"

namespace ravenscript
{
namespace fsm
{

class WordState : public State
{
public:
	explicit WordState(const char* word);

	virtual bool Parse(LexicalToken*& istream, LexicalToken* end) override;
	virtual bool IsAvailable(LexicalToken*& istream, LexicalToken* end) override;

private:
	const char* m_word;
};

}
}
