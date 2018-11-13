#include"Engine.h"
#include<iostream>
Object::Object()
	: va(nullptr), vb(nullptr), layout(nullptr), ib(nullptr), s(nullptr), t(nullptr)
{}
Object::~Object()
{
	delete va;
	delete vb;
	delete layout;
	delete ib;
	delete s;
	delete t;
	delete positions;
}

VertexArray *Object::getVertexArray()
{
	if (va==nullptr)
	{
		count = getPositions(positions);
		vb = new VertexBuffer(positions, count*sizeof(float));
		layout = new VertexBufferLayout();
		layout->Push_float(3);//default
		layout->Push_float(2);
		va->AddBuffer(*vb, *layout);
	}
	return va;
}
IndexBuffer *Object::getIndexBuffer(float *cam)
{
	unsigned int *indices;
	int count_indices = getIndices(cam, indices);
	auto ib = new IndexBuffer(indices, count_indices);
	return ib;
}
void Object::setShader(const std::string &name)
{
	s = new Shader(name.c_str());
}
Shader *Object::getShader()
{
	if (s==nullptr)
	{
		std::cout<<"Using default shader!\n"<<std::endl;
		s = new Shader("./resources/shaders/math.shader");
		this->setTexture("./resources/textures/world.png");

	}
	return s;
}
void Object::setTexture(const std::string &path)
{
	if (s==nullptr)
	{
		std::cout<<"Using default shader!\n"<<std::endl;
		s = new Shader("./resources/shaders/math.shader");
	}
	s->Bind();
	t = new Texture(path.c_str());
}
