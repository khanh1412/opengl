#ifndef _NORM_BUFFER_
#define _NORM_BUFFER_
class NormBuffer
{
	private:
		float *h_ptr;
		unsigned int count;
		bool writable;

		float *d_ptr;
	public:
		NormBuffer(const float *data, unsigned int count);
		NormBuffer(unsigned int count);
		~NormBuffer();

		void setData(const float *data, unsigned int count);
		void Bind() const;
		void Unbind() const;

		inline unsigned int GetCount() const {return count;}
		inline float *getDevicePointer() const {return d_ptr;}	
		inline float *getHostPointer() const {return h_ptr;}	
}
#endif
