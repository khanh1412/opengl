#include"Engine.h"

Object::Object()
{
	va = new VertexArray();
	genVertices();
	vb = new VertexBuffer(hm_vertices*sizeof(float));
	l = new VertexBufferLayout();
		l->Push_float(3);
		l->Push_float(2);
	va->AddBuffer(*vb, *l);
	genTriangles();
	ib = new IndexBuffer(hm_triangles);
	s = genShader();
	t = genTexture();
}


Object::~Object()
{
	cudaFree(vertices);
	cudaFree(triangles);

	delete va;
	delete vb;
	delete l;
	delete ib;
	delete s;
	delete t;
}
inline Shader *Object::genShader()
{
	return new Shader("./resources/shaders/math.shader");
}
inline Texture *Object::genTexture()
{
	return new Texture("./resouces/textures/a.png");
}
