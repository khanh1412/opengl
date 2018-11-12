#include"Engine"

Object::Object()
{}
Object::~Object()
{}
int Object::getCount()
{
	return count;
}
int Object::getCountIndices()
{
	return count_indices;
}
float *Object::getPositions()
{
	return positions;
}
float *Object::getIndices()
{
	return indices;
}