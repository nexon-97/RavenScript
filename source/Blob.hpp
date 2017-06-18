#pragma once
#include <iostream>

namespace ravenscript
{

struct Blob
{
	char* data;
	std::size_t size;

	Blob(char* data, std::size_t size)
		: data(data)
		, size(size)
	{}

	~Blob()
	{
		if (!!data)
		{
			delete[] data;
		}
	}
};

}
