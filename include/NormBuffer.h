#ifndef _NORM_BUFFER_
#define _NORM_BUFFER_
#include<cstddef>
class NormBuffer
{
	private:
		float *h_ptr;
		unsigned int count;
		bool writable;

	public:
		NormBuffer(float *data, unsigned int count);
		NormBuffer(unsigned int count);
		~NormBuffer();

		void setData(float *data, unsigned int count);
		void Bind() const {};
		void Unbind() const {};

		inline unsigned int GetCount() const {return count;}
		inline size_t getSize() const {return count*sizeof(float);}
		inline float *getHostPointer() const {return h_ptr;}	
};
#endif
