#include"Engine.h"
#include<iostream>
Engine::Engine(int Width, int Height, const std::string& name)
	: Width(Width), Height(Height), name(name), pov(0)
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
	glfwTerminate();
}

bool Engine::isClosed()
{
	return glfwWindowShouldClose(window);
}

void Engine::clear()
{
	renderer.Clear();
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
	cam = {x, y, z};
}
void Engine::setCenter(float x, float y, float z)
{
	center = {x, y, z};
}
void Engine::setUp(float x, float y, float z)
{
	up = {x, y, z};
}
void Engine::setPov(float a)
{
	pov = a;
}

void Engine::draw(Object *obj)
{
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
