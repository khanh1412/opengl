#include"Engine.h"
#include"Sphere.h"
#include"Rectangle.h"
#include"Cylinder.h"
#include<iostream>
#include<cmath>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS or action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_RIGHT)
                {
                }
                if (key == GLFW_KEY_LEFT)
                {
                }
                if (key == GLFW_KEY_UP)
                {
                }
                if (key == GLFW_KEY_DOWN)
                {
                }
	}
}
int main()
{
	Engine E(640, 480, "world");

	Object *O = new Rectangle(-1, 0, 1, -1, 0, -1, 1, 0, 1);
	O->setTexture("./resources/textures/a.png");
	


	glfwSwapInterval(1);

	while (!E.isClosed())
	{

		E.clear();
		
		E.setCam(0,0,2);
		E.setCenter(0,0,0);
		E.setUp(0,1,0);
		E.setPov(1.0);
		E.draw(O);

		E.swapBuffers();
		E.pollEvents();
		//glfwSetKeyCallback(E.getWindow(), key_callback);



	}

}
