#ifndef _ENGINE_H_
#define _ENGINE_H_

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
