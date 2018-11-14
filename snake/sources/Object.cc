#include"Engine.h"
#include<iostream>
Object::Object(bool vb_dynamic, bool ib_dynamic)
	: va(nullptr), vb(nullptr), layout(nullptr), ib(nullptr), s(nullptr), t(nullptr), vb_dynamic(vb_dynamic), ib_dynamic(ib_dynamic)
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
	delete indices;
}

void Object::genShader(const std::string& path)
{
	if (s) delete s;
	s = new Shader(path);
}
void Object::genTexture(const std::string& path)
{
	if (t) delete t;
	s->Bind();
	t = new Texture(path);
}

VertexArray *Object::getVertexArray()
{
	if (va == nullptr) //create VertexArray
	{
		va = new VertexArray();
		genPositions();
		genLayout();
		if (vb_dynamic)
			vb = new VertexBuffer(size);
		else
			vb = new VertexBuffer(positions, size);
		va->AddBuffer(*vb, *layout);
	}
	if (vb_dynamic) //Refresh if dynamic
	{
		genPositions();
		vb->setData(positions, size);
	}
	return va;
}
IndexBuffer *Object::getIndexBuffer(float *cam)
{
	if (ib == nullptr) //create IndexBuffer
	{
		genIndices(cam);
		if (ib_dynamic)
			ib = new IndexBuffer(count);
		else
			ib = new IndexBuffer(indices, count);
	}
	if (ib_dynamic) //Refresh if dynamic
	{
		genIndices(cam);
		ib->setData(indices, count);
	}
	return ib;
}
Shader *Object::getShader()
{
	if (s == nullptr)
	{
		genShader(default_shader_path);
		genTexture(default_texture_path);	
	}
	return s;
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

