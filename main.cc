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
int Sphere::getPositions(float*& positions)
{
	float texCoord1, texCoord2;
	float x, y, z;

	n = static_cast<int>((pi/2)/d);
	
	int count = (4*n+1)*(2*n+1) * 5;
	positions = new float[count];

	float *ptr = &(positions[0]);
		
	for (int a=0; a<=4*n; a++)
	for (int b=-n; b<=n; b++)
	{
		float alpha = static_cast<float>(a)*pi/(2*n);
		float beta = static_cast<float>(b)*pi/(2*n);
		y = r*std::sin(beta);
		x = r*std::cos(beta)*std::sin(alpha);
		z = r*std::cos(beta)*std::cos(alpha);

		texCoord1 = static_cast<float>(a)/(4*n);
		texCoord2 = 0.5f * (1.0f + static_cast<float>(b)/(n));

		ptr[0] = x;
		ptr[1]= y;
		ptr[2] = z;
		ptr[3] = texCoord1;
		ptr[4] = texCoord2;

		ptr += 5;
	}

	return count;
}

int Sphere::getIndices(float *cam, unsigned int*& indices)
{
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

					float vec_mul = cam[0]*center[0] + cam[1]*center[1] + cam[2]*center[2];
					if (vec_mul > r*r)

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
			int hm_indices = out_vec.size();
			indices = new unsigned int[hm_indices];

			for (int i=0; i<hm_indices; i++)
				indices[i] = out_vec.at(i);
			
			return hm_indices;
}




#include<iostream>
int main()
{
	Sphere S(1.0f, 0.1f);
	Engine E(640, 480, "world");
	while (!E.isClosed())
	{
		E.clear();
		E.setCam(0, 0, 2);
		E.setCenter(0, 0, 0);
		E.setUp(0,1,0);
		E.setPov(2.0);

		E.draw(&S);
		E.swapBuffers();
		E.pollEvents();
	}

}
