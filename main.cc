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

#include<ctime>
#include<cmath>
int main()
{
	Engine E(640, 480, "world");

	Object *R = new Rectangle(-1, -1, 0, -1, 1, 0, 1, -1, 0);
	Object *S = new Sphere(0, 0, 0, 0.5);
	S->setTexture("./resources/textures/a.png");
	
	Object *C = new Cylinder(0, 1, 0, 0, -1, 0, 0.5, 0.785);
	//C->setTexture("./resources/textures/a.png");


	float x = -1;
	float d = 0.01;

	glfwSwapInterval(1);
	while (!E.isClosed())
	{
		std::clock_t t0 = clock();

		x+= d;
		E.clear();
		E.setCam(2*std::sin(x), 0, 2*std::cos(x));
		
		E.setCenter(0, 0, 0);
		E.setUp(0,1,0);
		E.setPov(1.0);

		//E.draw(R);
		//E.draw(S);
		E.draw(C);
		E.swapBuffers();
		E.pollEvents();

		std::clock_t t1 = clock();
		std::cout<<"FPS : "<<static_cast<float>(CLOCKS_PER_SEC)/(t1-t0)<<std::endl;
		//glfwSetKeyCallback(E.getWindow(), key_callback);
		
	}

}
