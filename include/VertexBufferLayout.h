#ifndef _VERTEXBUFFERLAYOUT_H_
#define _VERTEXBUFFERlAYOUT_H_
#include<vector>
#include"Renderer.h"
struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT: 		return 4;
			case GL_UNSIGNED_INT: 	return 4;
			case GL_UNSIGNED_BYTE: 	return 1;
		}
		return 0;
	}
};
class VertexBufferLayout
{
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	public:
		VertexBufferLayout()
			: m_Stride(0) {}
		/*
		template<typename T>
		void Push(unsigned int count);
		template<>
		void Push<float>(unsigned int count);
		template<>
		void Push<unsigned int>(unsigned int count);
		template<>
		void Push<unsigned char>(unsigned int count);
		*/

		void Push_float(unsigned int count);
		void Push_unsigned_int(unsigned int count);
		void Push_unsigned_char(unsigned int count);


		inline const std::vector<VertexBufferElement> GetElements() const {return m_Elements;}
		inline unsigned int GetStride() const {return m_Stride;}
};
#endif
