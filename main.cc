#include<GL/glew.h>
#include<GLFW/glfw3.h>

int main(void)
{
	GLFWwindow* window;

	//intialize the library
	
	if (!glfwInit())
		return -1;
	glewInit();

	window = glfwCreateWindow(640, 480, "Hello World", 0x0, 0x0);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
