#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>


#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"VertexBufferLayout.h"
#include"Texture.h"


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

	std::cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<std::endl;

{


	float positions[] = 
	{
		-0.5f, -0.5f, 0.0f, 0.0f,//bottom left
		 0.5f, -0.5f, 1.0f, 0.0f,//bottom right
		 0.5f,  0.5f, 1.0f, 1.0f,//top right
		-0.5f,  0.5f, 0.0f, 1.0f //top left
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};


	VertexArray va;
	VertexBuffer vb(positions, 4*4*sizeof(float));
	VertexBufferLayout layout;
	layout.Push_float(2);//2 floats of rectangle vertices
	layout.Push_float(2);//2 floats of texture coordinates

	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);


	Shader shader("./resources/shaders/image2d.shader");
	shader.Bind();

	Texture texture("./resources/textures/a.png");
	texture.Bind();


	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();
	texture.Unbind();

	Renderer renderer;
	
	

	
	while (!glfwWindowShouldClose(window))
	{
		
		


		/* render here */
		renderer.Clear();

		
		texture.Bind(0);
		shader.SetUniform1i("u_Texture", 0);


		shader.Bind();
		va.Bind();
		ib.Bind();

		renderer.Draw(va, ib, shader);



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
} // detele everything before OpenGL terminate	

	glfwTerminate();
	return 0;
}
