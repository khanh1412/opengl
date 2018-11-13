#include"Engine.h"
#include"Sphere.h"
#include"Rectangle.h"
#include"Cylinder.h"
#include<iostream>
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS or action == GLFW_REPEAT)
	{
	}
}

int main()
{
	Engine E(640, 480, "world");


	Object *S = new Sphere(0.0, 0.0, 0.0, 0.1);
	//Object *R = new Rectangle(1, 0, 1, -1, 0, 1, 1, 1, 0);
	Object *C = new Cylinder(0, 1, 0.1, 0, 0, 0, 1);
	//R->setTexture("./resources/textures/a.png");
	while (!E.isClosed())
	{
		E.clear();
		E.setCam(0, 2, 2);
		E.setCenter(0, 0, 0);
		E.setUp(0,1,0);
		E.setPov(2.0);

	//	E.draw(R);
		E.draw(S);
		E.draw(C);
		E.swapBuffers();
		E.pollEvents();

		glfwSetKeyCallback(E.getWindow(), key_callback);
	}

}
