#ifndef _RENDERER_H_
#define _RENDERER_H_

#include<GL/glew.h>


#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))
static void CLClearError();
static bool GLLogCall(const char* function, const char* file, int line);




#endif
