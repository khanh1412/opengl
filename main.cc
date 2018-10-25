#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

int main(void)
{
	GLFWwindow* window;

	//intialize the library
	
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 480, "Hello World", 0x0, 0x0);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
		std::cout<< "Error!"<<std::endl;

	std::cout<<glGetString(GL_VERSION)<<std::endl;

	//prepare buffer

	float position[6] = 
	{
		-0.5, -0.5,
		 0.0,  0.5,
		 0.5, -0.5
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), &(position[0]), GL_STATIC_DRAW);

	//end prepare buffer

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//render

		glDrawArrays(GL_TRIANGLES, 0, 3);



		//end render
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
