#include"Engine.h"
#include"Sphere.h"
#include"Rectangle.h"
#include"Cylinder.h"
#include<iostream>
#include<cmath>
Object *grass;
Object *ball;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS or action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_RIGHT)
                {
			ball->rotate(0, 0.1, 0);
                }
                if (key == GLFW_KEY_LEFT)
                {
			ball->rotate(0, -0.1, 0);
                }
                if (key == GLFW_KEY_UP)
                {
			ball->rotate(-0.1, 0, 0);
                }
                if (key == GLFW_KEY_DOWN)
                {
			ball->rotate(0.1, 0, 0);
                }
	}
}
#include<ctime>
int main()
{
	Engine E(640, 480, "world");

	grass = new Rectangle(-20, 0, 20, -20, 0, -20, 20, 0, 20);
	grass->setTexture("./resources/textures/grass.png");
	ball = new Sphere(0, 1, 0, 10, 0.1);
	ball->setTexture("./resources/textures/world.png");
	


	glfwSwapInterval(1);

	while (!E.isClosed())
	{
		std::clock_t t1 = std::clock();

		E.clear();
			

		E.setCam(0, 10, 20);
		E.setCenter(0, 1, 0);
		E.setUp(0,1,0);
		E.setPov(1.0);
		//E.draw(grass);
		E.draw(ball);		

		E.swapBuffers();
		E.pollEvents();
		glfwSetKeyCallback(E.getWindow(), key_callback);

		std::clock_t t2 = std::clock();
		std::cout<<"FPS : "<<static_cast<float>(CLOCKS_PER_SEC)/(t2-t1)<<std::endl;


	}

}
