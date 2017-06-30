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

	virtual ast::NodePtr Parse(LexicalToken*& istream, LexicalToken* end, const ast::NodePtr& inputNode) override;
	virtual bool IsAvailable(LexicalToken*& istream, LexicalToken* end) override;

private:
	const char* m_word;
};

}
}
