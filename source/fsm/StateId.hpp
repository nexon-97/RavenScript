#pragma once

namespace ravenscript
{
namespace fsm
{

enum class StateId
{
	None,
	BraceOpen,
	BraceClose,
	Expression,
	Operator,
	Identifier,
	Statement,
	Program,
	Comma,
};

}
}
