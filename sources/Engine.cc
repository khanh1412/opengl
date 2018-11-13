#include"Engine.h"
#include<iostream>
Engine::Engine()
	: Engine(640, 480, "hello world")
{}

Engine::Engine(int Width, int Height, const std::string &name)
	: Width(Width), Height(Height), name(new std::string(name)), renderer(new Renderer()), cam(nullptr), center(nullptr), pov(0)
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
	Shader *s = obj->getShader();
	VertexArray *va = obj->getVertexArray();
	IndexBuffer *ib = obj->getIndexBuffer(cam);

	va->Bind();
	s->Bind();
	glm::mat4 P = glm::perspective(pov, static_cast<float>(Height)/static_cast<float>(Width), 0.0f, 100.0f);
	glm::vec3 cam(this->cam[0], this->cam[1], this->cam[2]);
	glm::vec3 center(this->center[0], this->center[1], this->center[2]);
	glm::vec3 up(this->up[0], this->up[1], this->up[2]);

	glm::mat4 V = glm::lookAt(cam, center, up);

	glm::mat4 MVP = P*V;

	s->SetUniformMat4f("u_MVP", MVP);

	renderer->Draw(*va, *ib, *s);
	std::cout<<"draw!\n";
}

