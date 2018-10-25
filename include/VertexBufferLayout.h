#ifndef _VERTEXBUFFERLAYOUT_H_
#define _VERTEXBUFFERlAYOUT_H_
#include<vector>
#include"Renderer.h"
struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type);
};
class VertexBufferLayout
{
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	public:
		VertexBufferLayout()
			: m_Stride(0) {}

		void Push_float(unsigned int count);
		void Push_unsigned_int(unsigned int count);
		void Push_unsigned_char(unsigned int count);


		inline const std::vector<VertexBufferElement> GetElements() const {return m_Elements;}
		inline unsigned int GetStride() const {return m_Stride;}
};
void VertexBufferLayout::Push_float(unsigned int count)
{
	m_Elements.push_back( {GL_FLOAT, count, GL_FALSE} );
	m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
}
void VertexBufferLayout::Push_unsigned_int(unsigned int count)
{
	m_Elements.push_back( {GL_UNSIGNED_INT, count, GL_FALSE} );
	m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
}
void VertexBufferLayout::Push_unsigned_char(unsigned int count)
{
	m_Elements.push_back( {GL_UNSIGNED_BYTE, count, GL_TRUE} );
	m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}
unsigned int VertexBufferElement::GetSizeOfType(unsigned int type);
{
	switch (type)
	{
		case GL_FLOAT: 		return 4;
		case GL_UNSIGNED_INT: 	return 4;
		case GL_UNSIGNED_BYTE: 	return 1;
	}
	return 0;
}
#endif
