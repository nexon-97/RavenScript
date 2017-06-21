#pragma once
#include <iostream>
#include <memory>

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

using BlobPtr = std::shared_ptr<Blob>;

}
