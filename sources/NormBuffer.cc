#include"NormBuffer.h"

NormBuffer::NormBuffer(const float *data, unsigned int count)
	: h_ptr(data), d_ptr(nullptr), count(0), writable(false), count(count)
{}
NormBuffer::NormBuffer(unsigned int count)
	: h_ptr(data), d_ptr(nullptr), count(0), writable(true), count(count)
{}
NormBuffer::~NormBuffer()
{

}

void NormBuffer::setData(const float *data, unsigned int count)
{
	if (not writable) return;
	if (count > this->count)
	{
		std::cout<<"Set a larger data than buffer size!"<<std::endl;
		__builtin_trap();
	}
	else 
	{
		if (count < this->count)
			std::cout<<"Set a smaller data than buffer size!"<<std::endl;
		h_ptr = data;
	}
}
void NormBuffer::
