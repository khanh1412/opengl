#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>

#include"ParseShader.h"

#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"








int main(void)
{
	//intialize the library
	
	if (!glfwInit())
		return -1;

	GLFWwindow *window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
		std::cout<< "Error!"<<std::endl;

	std::cout<<glGetString(GL_VERSION)<<std::endl;

	{
	//prepare buffer
	float positions[12] = 
	{
		-0.5f, -0.5f,//0
		 0.5f, -0.5f,//1
		 0.5f,  0.5f,//2
		-0.5f,  0.5f //3
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	/*
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	*/

	VertexArray va;
	VertexBuffer vb(positions, 4*2*sizeof(float));
	VertexBufferLayout layout;
	layout.Push_float(2);

	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);


	std::string vertexShader;
	std::string fragmentShader;

	ParseShader("./resources/shader/basic.shader", vertexShader, fragmentShader);

	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);


	//end prepare buffer

	while (!glfwWindowShouldClose(window))
	{
		//render
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		//end render
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shader);
	}

	glfwTerminate();
	return 0;
}
