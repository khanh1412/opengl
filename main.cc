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


void renderScene()
{
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGB,
		WIDTH,
		HEIGHT,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		&texture[0][0][0]		
	);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0, -1.0);
		glTexCoord2f(1.0f, 0.0f); glVertex2f( 1.0, -1.0);
		glTexCoord2f(1.0f, 1.0f); glVertex2f( 1.0,  1.0);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0,  1.0);
	glEnd();

	glFlush();
	glutSwapBuffers();
}


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


	float positions[] = 
	{
		-0.5f, -0.5f, 0.0f, 0.0f,//0
		 0.5f, -0.5f, 1.0f, 0.0f,//1
		 0.5f,  0.5f, 1.0f, 1.0f,//2
		-0.5f,  0.5f, 0.0f, 1.0f //3
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



	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();


	Renderer renderer;
	
	

	
	while (!glfwWindowShouldClose(window))
	{
		
		


		/* render here */
		renderer.Clear();

		shader.Bind();
		
		Texture texture("./resources/textures/Le.png");
		texture.Bind(0);
		shader.SetUniform1i("u_Texture", 0);



		va.Bind();
		ib.Bind();

		renderer.Draw(va, ib, shader);



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	}

	glfwTerminate();
	return 0;
}
