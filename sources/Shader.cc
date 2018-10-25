#include"Shader.h"
Shader::Shader(const std::string& filename)
	: m_FilePath(filename), m_RendererID(0)
{
	CompileShader();
}
~Shader();

void Shader::Bind() const;
void Shader::UnBind() const;

void Shader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
unsigned int Shader::GetUniformLocation(const std::string& name);










bool Shader::CompileShader()
