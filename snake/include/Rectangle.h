#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_
#include"Engine.h"
class Rectangle: public Object
{
	private:
		float bl[3];
		float tl[3];
		float br[3];
	protected:
		int getPositions(float*& positions);
		int getIndices(float *cam, unsigned int*& indices);
	public:
		Rectangle(float x1=0.0f, float y1=0.0f, float z1=0.0f, float x2=0.0f, float y2=0.0f, float z2=0.0f, float x3=0.0f, float y3=0.0f, float z3=0.0f);
		~Rectangle();
};
#endif
