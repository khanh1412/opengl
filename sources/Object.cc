#include"Engine.h"
#include<iostream>
Object::Object()
	: va(nullptr), vb(nullptr), layout(nullptr), ib(nullptr), s(nullptr), t(nullptr)
{
	Shift[0] = 0;
	Shift[1] = 0;
	Shift[2] = 0;
	Rotate[0] = 0;
	Rotate[1] = 0;
	Rotate[2] = 0;
	Scale[0] = 1;
	Scale[1] = 1;
	Scale[2] = 1;
}
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
		va = new VertexArray();
		count = getPositions(positions);
		vb = new VertexBuffer(positions, count*sizeof(float));
		layout = new VertexBufferLayout();
		layout->Push_float(3);//default
		layout->Push_float(2);
		va->AddBuffer(*vb, *layout);
	}
	va->Bind();
	return va;
}
IndexBuffer *Object::getIndexBuffer(float *cam)
{
	unsigned int *indices;
	int count_indices = getIndices(cam, indices);
	auto ib = new IndexBuffer(indices, count_indices);
	ib->Bind();
	delete indices;
	return ib;
}
void Object::setShader(const std::string &name)
{
	s = new Shader(name);
}
Shader *Object::getShader()
{
	if (s==nullptr)
	{
		//std::cout<<"Using default shader and texture!\n"<<std::endl;
		s = new Shader("./resources/shaders/math.shader");
		this->setTexture("./resources/textures/world.png");

	}
	s->Bind();
	return s;
}
void Object::setTexture(const std::string &path)
{
	if (s==nullptr)
	{
		//std::cout<<"Using default shader!\n"<<std::endl;
		s = new Shader("./resources/shaders/math.shader");
	}
	s->Bind();
	t = new Texture(path);
	t->Bind();
}
Texture *Object::getTexture()
{
	if (t==nullptr)
		this->getShader();
	t->Bind();
	return t;
}

void Object::setShift(float x, float y, float z)
{
	Shift[0] = x;
	Shift[1] = y;
	Shift[2] = z;
}
void Object::setRotate(float x, float y, float z)
{
	Rotate[0] = x;
	Rotate[1] = y;
	Rotate[2] = z;
}
void Object::setScale(float x, float y, float z)
{
	Scale[0] = x;
	Scale[1] = y;
	Scale[2] = z;
}
void Object::shift(float x, float y, float z)
{
	Shift[0] += x;
	Shift[1] += y;
	Shift[2] += z;
}
void Object::rotate(float x, float y, float z)
{
	Rotate[0] += x;
	Rotate[1] += y;
	Rotate[2] += z;
}
void Object::scale(float x, float y, float z)
{
	Scale[0] += x;
	Scale[1] += y;
	Scale[2] += z;
}
float *Object::getShift()
{
	return &(Shift[0]);
}
float *Object::getRotate()
{
	return &(Rotate[0]);
}
float *Object::getScale()
{
	return &(Scale[0]);
}

