#ifndef _SHADER_H_
#define _SHADER_H_
#include<string>
class Shader
{
	private:
		std::string m_FilePath;
		unsigned int m_RendererID;
	public:
		Shader(const std::string& filename);
		~Shader();

		void Bind() const;
		void UnBind() const;

		//set uniform
		void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
	private:
		unsigned int GetUniformLocation(const std::string& name);
		bool CompileShader();
}

#endif
