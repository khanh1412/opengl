#include"Engine.h"
#include"Sphere.h"
#include"Rectangle.h"
#include"Cylinder.h"
#include<iostream>
#include<cmath>

float direction[] = {0, 0, -1};

float cam_to_grass[] = {0, 40, 20};
float cam_to_ball[] = {0, 40, 20};
float grass_center[] = {0, 1, 0};

bool out()
{
	return false;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS or action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_RIGHT)
                {
			if (not out())
			{
				int n = 1000000;
				float vec[3];
				for (int i=0; i<n; i++)
				{
					vec[0] = direction[2];
					vec[2] = direction[0];
					direction[0] += 0.01*vec[0]/n;
					direction[2] += 0.01*vec[2]/n;
					cam_to_ball[0] -= 0.01*20*vec[0]/n;
					cam_to_ball[1] -= 0.01*20*vec[1]/n;
					cam_to_grass[0] -= 0.01*20*vec[0]/n;
					cam_to_grass[0] -= 0.01*20*vec[1]/n;
				}
			}
                }
                if (key == GLFW_KEY_LEFT)
                {
			if (not out())
			{
				int n = 1000000;
				float vec[3];
				for (int i=0; i<n; i++)
				{
					vec[0] = -direction[2];
					vec[2] = -direction[0];
					direction[0] += 0.01*vec[0]/n;
					direction[2] += 0.01*vec[2]/n;
					cam_to_ball[0] -= 0.01*20*vec[0]/n;
					cam_to_ball[1] -= 0.01*20*vec[1]/n;
					cam_to_grass[0] -= 0.01*20*vec[0]/n;
					cam_to_grass[0] -= 0.01*20*vec[1]/n;
				}
			}
                }
                if (key == GLFW_KEY_UP)
                {
			if (not out())
			{
				grass_center[0] += direction[0];
				grass_center[1] += direction[1];
				grass_center[2] += direction[2];

				cam_to_grass[0] += direction[0];
				cam_to_grass[1] += direction[1];
				cam_to_grass[2] += direction[2];
			}
                }
                if (key == GLFW_KEY_DOWN)
                {
			if (not out())
			{
				grass_center[0] -= direction[0];
				grass_center[1] -= direction[1];
				grass_center[2] -= direction[2];

				cam_to_grass[0] -= direction[0];
				cam_to_grass[1] -= direction[1];
				cam_to_grass[2] -= direction[2];
			}
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
		

		E.setCam(cam_to_grass[0], cam_to_grass[1], cam_to_grass[2]);
		E.setCenter(grass_center[0], grass_center[1], grass_center[2]);
		E.setUp(0,1,0);
		E.setPov(1.0);
		E.draw(grass);
		
		E.setCam(cam_to_ball[0], cam_to_ball[1], cam_to_ball[2]);
		E.setCenter(0,1,0);
		E.setUp(0,1,0);
		E.setPov(1.0);
		E.draw(ball);

		E.swapBuffers();
		E.pollEvents();
		glfwSetKeyCallback(E.getWindow(), key_callback);



	}

}
