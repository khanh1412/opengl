#ifndef _VERTEX_ARRAY_
#define _VERTEX_ARRAY_

#include"VertexBuffer.h"
//#include"VertexBufferLayout.h"

class VertexBufferLayout;
class VertexArray
{
	private:
		unsigned int m_RendererID;
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
		void Bind() const;
		void Unbind() const;
};
#include"VertexBufferLayout.h"
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i=0; i<elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type,  element.normalized , layout.GetStride(), reinterpret_cast<const void*>(offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}
void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}
void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
#endif
