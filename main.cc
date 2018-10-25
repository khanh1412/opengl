#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>


#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"







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


	VertexArray va;
	VertexBuffer vb(positions, 4*2*sizeof(float));
	VertexBufferLayout layout;
	layout.Push_float(2);

	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);


	Shader shader("./resources/shaders/basic.shader");
	shader.Bind();

	shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);


	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();


	


	float r = 0.0f;
	float inc = 0.05f;

	while (!glfwWindowShouldClose(window))
	{
		/* render here */
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Bind();
		shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
	
		va.Bind();
		ib.Bind();


		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


		if (r>1.0f)
			inc = -0.05f;
		else if (r<0.0f)
			inc = 0.05f;
		r += inc;







		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	}

	glfwTerminate();
	return 0;
}
