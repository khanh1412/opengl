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

class Object
{
	private:
		int count;
		float *position;
		int count_indices;
		unsigned int *indices;
	public:
		Object();
		virtual ~Objects();
		int getCount();
		int getCountIndices();
		float *getPositions();
		float *getIndices();

		virtual void genIndices(float *cam)=0;

};


#endif
