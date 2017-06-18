#pragma once

namespace ravenscript
{

class Stack
{
public:
	Stack();
	virtual ~Stack();

	void PushInteger(int data);
	void PushBoolean(bool data);
	void PushFloat(float data);
	void PushUserdata(void* data, int size);

	int PopInteger();
	bool PopBoolean();
	float PopFloat();
	void* PopUserdata();

	void SetBottom(int bottom);
	int GetBottom() const;

	void AddFrame();

protected:
	int m_top;
	int m_bottom;
	char* m_memoryBlob;
};

}
