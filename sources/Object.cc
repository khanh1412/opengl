#include"Engine.h"
#include<iostream>
Object::Object()
	: va(nullptr), vb(nullptr), layout(nullptr), ib(nullptr), s(nullptr), t(nullptr)
{
	shift[0] = 0;
	shift[1] = 0;
	shift[2] = 0;
	rotate[0] = 0;
	rotate[1] = 0;
	rotate[2] = 0;
	scale[0] = 1;
	scale[1] = 1;
	scale[2] = 1;
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
	shift[0] = x;
	shift[1] = y;
	shift[2] = z;
}
void Object::setRotate(float x, float y, float z)
{
	rotate[0] = x;
	rotate[1] = y;
	rotate[2] = z;
}
void Object::setScale(float x, float y, float z)
{
	scale[0] = x;
	scale[1] = y;
	scale[2] = z;
}
float *Object::getShift()
{
	return &(shift[0]);
}
float *Object::getRotate()
{
	return &(rotate[0]);
}
float *Object::getScale()
{
	return &(scale[0]);
}

