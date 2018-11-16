#ifndef _OBJECT_H_
#define _OBJECT_H_
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
		virtual void genVertices()=0;
		virtual void genTriangles()=0;

		/* genIndices generates visible triangles using 3 algorithms
		 * 	1. Break triangles down
		 * 	2. Draw from far to near
		 * 	3. Norm vectors
		 * */
		virtual void genIndices(float x, float y, float z)=0;

	public:
		void importShader(std::string& path);
		void importTexture(std::string& path);
	public:
		Object();
		~Object();





















};
#endif
