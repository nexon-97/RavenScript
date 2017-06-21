#pragma once

namespace ravenscript
{

struct ProductionId
{
	enum
	{
		Program,
		Identifier,
		Number,
		Expression,
		Statement,
		Module,
		LValue,
		Count
	};
};

}
