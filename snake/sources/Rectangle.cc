#include"Rectangle.h"

Rectangle::Rectangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
	bl[0] = x1;
	bl[1] = y1;
	bl[2] = z1;
	tl[0] = x2;
	tl[1] = y2;
	tl[2] = z2;
	br[0] = x3;
	br[1] = y3;
	br[2] = z3;
}
Rectangle::~Rectangle()
{}

int Rectangle::getPositions(float*& positions)
{
	positions = new float[5*4];
	positions[0] = bl[0]; //bottom left
	positions[1] = bl[1];
	positions[2] = bl[2];
	positions[3] = 0;
	positions[4] = 0;
	positions[5] = tl[0]; //top left
	positions[6] = tl[1];
	positions[7] = tl[2];
	positions[8] = 0;
	positions[9] = 1;
	positions[10] = br[0]; //bottom right
	positions[11] = br[1];
	positions[12] = br[2];
	positions[13] = 1;
	positions[14] = 0;
	positions[15] = tl[0] + br[0] - bl[0]; //top right
	positions[16] = tl[1] + br[1] - bl[1];
	positions[17] = tl[2] + br[2] - bl[2];
	positions[18] = 1;
	positions[19] = 1;
	return 5*4;
}
int Rectangle::getIndices(float *cam, unsigned int*& indices)
{
	indices = new unsigned int[6];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;
	return 6;
}
