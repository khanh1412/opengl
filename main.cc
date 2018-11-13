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

	Object *grass = new Rectangle(-20, 0, 20, -20, 0, -20, 20, 0, 20);
	grass->setTexture("./snake/resources/textures/grass.png");
	Object *ball = new Sphere(0, 1, 0, 1, 0.01);
	ball->setTexture("./resources/textures/a.png");
	


	glfwSwapInterval(1);

	float x =0;
	float d = 0.01;
	while (!E.isClosed())
	{

		E.clear();
		
		if (x > 1 or x<0)
			d = -d;
		x+= d;
		

		E.setCam(0, 40, 20);
		E.setCenter(0, 1, 0);
		E.setUp(0,1,0);
		E.setPov(1.0);
		E.draw(grass);
		E.draw(ball);		

		E.swapBuffers();
		E.pollEvents();
		glfwSetKeyCallback(E.getWindow(), key_callback);



	}

}
