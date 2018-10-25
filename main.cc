#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>


#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"VertexBufferLayout.h"


#include<cmath>



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

	glfwSwapInterval(1);

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


	Renderer renderer;
	
	

	float r = 1.0f;
	float g = 0.0f;
	float b = 0.0f;
	float alpha = 0.0f;

	
	while (!glfwWindowShouldClose(window))
	{
		
		alpha += 0.05f;

		r = std::cos(alpha);
		g = std::cos(2.0944 - alpha);
		b = std::cos(4.1888 - alpha);

		


		/* render here */
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Bind();
		shader.SetUniform4f("u_Color", r, g, b, 1.0f);
	
		va.Bind();
		ib.Bind();

//		renderer.Draw(va, ib, shader);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	}

	glfwTerminate();
	return 0;
}
