#include"NormBuffer.h"
#include<iostream>
NormBuffer::NormBuffer(float *data, unsigned int count)
	: h_ptr(data), count(count), writable(false)
{}
NormBuffer::NormBuffer(unsigned int count)
	: h_ptr(nullptr), count(count), writable(true)
{}
NormBuffer::~NormBuffer()
{}

void NormBuffer::setData(float *data, unsigned int count)
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
