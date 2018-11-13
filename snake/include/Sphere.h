#include"Engine.h"
class Sphere: public Object
{
	private:
		float r;
		float d;
		float pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;

		int n;
	protected:
		int getPositions(float*& positions);
		int getIndices(float *cam, unsigned int*& indices);
	public:
		Sphere(float r, float d)
			: r(r), d(d)
		{}
		~Sphere()
		{}
};
