#ifndef _ENGINE_H_
#define _ENGINE_H_

#include"GL/glew.h"
#include"GLFW/glfw3.h"

#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"VertexBufferLayout.h"
#include"Texture.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include<string>

class Object
{
	protected:
		VertexArray *va;
		VertexBuffer *vb;
		VertexBufferLayout *layout;
		IndexBuffer *ib;
		Shader *s;
		Texture *t;

		float *positions;
		int count;
		
		virtual int getPositions(float*& positions)=0;
		virtual int getIndices(float *cam, unsigned int*& indices)=0;

	public:
		Object();
		~Object();
		VertexArray *getVertexArray();
		IndexBuffer *getIndexBuffer(float *cam);

		void setShader(const std::string &path);
		Shader *getShader();
		void setTexture(const std::string &path);

};
class Engine
{
	private:
		Renderer *renderer;
		GLFWwindow *window;
		int Width, Height;
		std::string *name;

		float *cam;
		float *center;
		float *up;
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
		void setCam(float x, float y, float z);
		void setCenter(float x, float y, float z);
		void setUp(float x, float y, float z);
		void setPov(float a);

		GLFWwindow *getWindow();
};

#endif
