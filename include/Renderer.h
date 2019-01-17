#ifndef _RENDERER_H_
#define _RENDERER_H_
#define ASSERT(x) if (!(x)) __builtin_trap()
#include<GL/glew.h>

#include"VertexArray.h"
#include"IndexBuffer.h"
#include"Shader.h"

class Renderer
{
	public:
		void Clear();
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}


#endif
