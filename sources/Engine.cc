#include"Engine.h"
#include<iostream>
Engine::Engine(int Width, int Height, const std::string &name)
	: Width(Width), Height(Height), name(new std::string(name)), renderer(new Renderer()), cam(nullptr), center(nullptr), up(nullptr), pov(0)
{
	if (!glfwInit())
	{
		std::cout<<"glfwInit failed!"<<std::endl;
		__builtin_trap();
		return;
	}

	window = glfwCreateWindow(Width, Height, name.c_str(), nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		std::cout<<"window creation failed!"<<std::endl;
		__builtin_trap();
		return;
	}
	else
	{
		std::cout<<"window created "<<Width<<"x"<<Height<<std::endl;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		std::cout<< "GLEW Error!"<<std::endl;
		__builtin_trap();
	}

	std::cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<std::endl;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
Engine::~Engine()
{
	delete renderer;
	delete name;
	glfwTerminate();
}

bool Engine::isClosed()
{
	return glfwWindowShouldClose(window);
}

void Engine::clear()
{
	renderer->Clear();
}
void Engine::swapBuffers()
{
	glfwSwapBuffers(window);
}
void Engine::waitEvents()
{
	glfwWaitEvents();
}
void Engine::pollEvents()
{
	glfwPollEvents();
}

void Engine::setCam(float x, float y, float z)
{
	if (cam==nullptr)
		cam = new float[3];
	cam[0] = x;
	cam[1] = y;
	cam[2] = z;
}
void Engine::setCenter(float x, float y, float z)
{
	if (center==nullptr)
		center = new float[3];
	center[0] = x;
	center[1] = y;
	center[2] = z;
}
void Engine::setUp(float x, float y, float z)
{
	if (up==nullptr)
		up = new float[3];
	up[0] = x;
	up[1] = y;
	up[2] = z;
}
void Engine::setPov(float a)
{
	pov = a;
}

void Engine::draw(Object *obj)
{

	float *shift = obj->getShift();
	float *rotate = obj->getRotate();
	float *scale = obj->getScale();


	Shader *s = obj->getShader();
	glm::mat4 Model(1.0f), View, Projection;

	Projection = glm::perspective(pov, static_cast<float>(Width)/static_cast<float>(Height), 0.0f, 1000.0f);

	View = glm::lookAt(glm::vec3(cam[0], cam[1], cam[2]), glm::vec3(center[0], center[1], center[2]), glm::vec3(up[0], up[1], up[2]));

	Model = glm::translate(Model, glm::vec3(shift[0], shift[1], shift[2]));
	Model = glm::rotate(Model, rotate[0], glm::vec3(1.0f, 0.0f, 0.0f));
	Model = glm::rotate(Model, rotate[1], glm::vec3(0.0f, 1.0f, 0.0f));
	Model = glm::rotate(Model, rotate[2], glm::vec3(0.0f, 0.0f, 1.0f));
	Model = glm::scale(Model, glm::vec3(scale[0], scale[1], scale[2]));

	
	s->SetUniformMat4f("u_Projection", Projection);
	s->SetUniformMat4f("u_View", View);
	s->SetUniformMat4f("u_Model", Model);
	/*
	glm::vec4 v(cam[0], cam[1], cam[2], 1.0f);
	v = Projection*View*Model*v;

	float obj_cam[3] = {v[0]/v[3], v[1]/v[3], v[2]/v[3]};
	*/
	float *obj_cam = cam;


	VertexArray *va = obj->getVertexArray();
	IndexBuffer *ib = obj->getIndexBuffer(&(obj_cam[0]));

	Texture *t = obj->getTexture();


	
	renderer->Draw(*va, *ib, *s);
	delete ib;
}
void Engine::draw(std::vector<Object*> *objs)
{
	for (int i=0; i<objs->size(); i++)
		draw(objs->at(i));
}

GLFWwindow *Engine::getWindow()
{
	return window;
}
