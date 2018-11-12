#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include<iostream>


#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"VertexBufferLayout.h"
#include"Texture.h"

#include<cmath>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#define HEIGHT 640
#define WIDTH 640


float pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;


class Sphere
{
	private:
		int n;
		int count;
		float *positions;
		int hm_indices;
		unsigned int *indices;
	public:
		Sphere(float r = 1.0f, float d = 0.001f)
		{
			float texCoord1, texCoord2;
			float x, y, z;

			n = static_cast<int>((pi/2)/d);
	
			count = (4*n+1)*(2*n+1) * 5;
			positions = new float[count];

			float *ptr = &(positions[0]);
		
			for (int a=0; a<=4*n; a++)
			for (int b=-n; b<=n; b++)
			{
				float alpha = a*pi/(2*n);
				float beta = b*pi/(2*n);

				y = r*std::sin(beta);
				x = r*std::cos(beta)*std::sin(alpha);
				z = r*std::cos(beta)*std::cos(alpha);

				texCoord1 = a/(4*n);
				texCoord2 = 0.5f * (1.0f + b/n);

				ptr[0] = x; ptr[1]= y; ptr[2] = z; ptr[3] = texCoord1; ptr[4] = texCoord2;

				ptr += 5;

			}
		}
		~Sphere()
		{
			delete positions;
		}

		int getCount()
		{
			return count;
		}

		float *getPositions()
		{
			return positions;
		}
		int getCountIndices()
		{
			return hm_indices;
		}
		unsigned int *getIndices()
		{
			return indices;
		}

		void genIndices(float *cam_pos)
		{
			delete indices;
			float center[3];

			std::vector<int> out_vec;
			int index = 0;
			for (int a=0; a<=4*n; a++)
			for (int b=-n; b<=n; b++)
			{
				if (a != 4*n and b != n)
				{
					int bl = index;
					int tl = bl + 1;
					int br = index + (2*n+1);
					int tr = br + 1;
					
					center[0] = (positions[5*bl+0] + positions[5*tr+0])/2;
					center[1] = (positions[5*bl+1] + positions[5*tr+1])/2;
					center[2] = (positions[5*bl+2] + positions[5*tr+2])/2;

					float vec_mul = cam_pos[0]*center[0] + cam_pos[1]*center[1] + cam_pos[2]*center[2];
					if (vec_mul > 0.0f)

					{
						out_vec.push_back(bl);
						out_vec.push_back(br);
						out_vec.push_back(tl);
						out_vec.push_back(tl);
						out_vec.push_back(tr);
						out_vec.push_back(br);
					}
				}
				index++;
			}
			hm_indices = out_vec.size();
			indices = new unsigned int[hm_indices];

			for (int i=0; i<hm_indices; i++)
				indices[i] = out_vec.at(i);
		}

};


int main(void)
{
	//intialize the library
	
	if (!glfwInit())
		return -1;

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", nullptr, nullptr);

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

	/*
	float positions[] = 
	{
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,//bottom left
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,//bottom right
		 0.0f, -1.0f,-1.0f, 0.5f, 0.0f,//bottom middle
		 0.0f,  1.0f,-1.0f, 0.5f, 1.0f,//top middle
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,//top right
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f //top left
	};

	unsigned int indices1[] =
	{
		0, 2, 5,
		2, 3, 5,
		2, 1, 3,
		3, 4, 1
	};
	unsigned int indices2[] =
	{
		1, 2, 4,
		2, 3, 4,
		2, 0, 3,
		3, 5, 0
	};

	*/
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Sphere S(1.0f, 0.1f);

	VertexArray va;
	VertexBuffer vb(S.getPositions(), S.getCount()*sizeof(float));


	VertexBufferLayout layout;
	layout.Push_float(3);//2 floats of rectangle vertices
	layout.Push_float(2);//2 floats of texture coordinates

	va.AddBuffer(vb, layout);

	Shader shader("./resources/shaders/math.shader");
	shader.Bind();

	Texture texture("./resources/textures/a.png");
	texture.Bind();

	Renderer renderer;
	
	

	float alpha = 0, beta = 0;
	float cam_pos[3];

	while (!glfwWindowShouldClose(window))
	{
		
		/* render here */
		renderer.Clear();


		texture.Bind(0);
		shader.SetUniform1i("u_Texture", 0);
		
		alpha += 0.01;
		beta += 0.01;

		cam_pos[0] = 2*std::sin(alpha);
		cam_pos[1] = 0.0f;
		cam_pos[2] = 2*std::cos(alpha);



		{
		glm::vec3 cam(cam_pos[0], cam_pos[1], cam_pos[2]);
		}

		{
			S.genIndices(cam_pos);
			IndexBuffer ib(S.getIndices(), S.getCountIndices());
			renderer.Draw(va, ib, shader);
		}
		
		
		


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
} // detele everything before OpenGL terminate	

	glfwTerminate();
	return 0;
}
