#ifndef _ENGINE_H_
#define _ENGINE_H_

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include"Renderer.h"
#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"Texture.h"
#include"CudaResource.h"
#include"CudaBuffer.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

class Object
{
	private:
		cudaStream_t stream;

		float *vertices;
		int hm_vertices;
		unsigned int *triangles;
		int hm_triangles;



		VertexArray *va;
		VertexBuffer *vb;
		VertexBufferLayout *l;
		IndexBuffer *ib;
		Shader *s;
		Texture *t;

	public: // Theses methods issue some CUDA kernels.
		/* genVertices and genTriangles generate data in GPU
		 * */
		virtual void genVertices();
		virtual void genTriangles();

		/* genIndices generates visible triangles using 3 algorithms
		 * 	1. Break triangles down
		 * 	2. Draw from far to near
		 * 	3. Norm vectors
		 * */
		virtual void genIndices(float x, float y, float z)=0;

	private:
		virtual Shader* genShader();
		virtual Texture* genTexture();

	public:
		Object();
		~Object();
};
class Engine
{
	private:
		Renderer renderer;
		GLFWwindow *window;
		int Width, Height;
		std::string name;

		glm::vec3 cam;
		glm::vec3 center;
		glm::vec3 up;
		float pov;

	public:
		Engine(int Width, int Height, const std::string &name);
		~Engine();
		bool isClosed();
		void clear();
		void swapBuffers();
		void waitEvents();
		void pollEvents();

		void draw(Object *obj);
		void draw(std::vector<Object*> *objs);
		void setCam(float x, float y, float z);
		void setCenter(float x, float y, float z);
		void setUp(float x, float y, float z);
		void setPov(float a);

		GLFWwindow *getWindow();
};

#endif
