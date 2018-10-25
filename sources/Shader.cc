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

void ParseShader(const std::string& filepath, std::string& VertexShader, std::string& FragmentShader)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	ShaderType type = ShaderType::NONE;

	std::string line;
	std::stringstream s[2];
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			s[int(type)] << line << "\n";
		}
	}

	VertexShader = s[0].str();
	FragmentShader = s[1].str();
}
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char *src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		std::cout<<"Failed to compile"<<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<<" shader!"<<std::endl;
		std::cout<<message<<std::endl;
		glDeleteShader(id);
		delete message;
		return 0;
	}
	return id;
}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program =  glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	
	glLinkProgram(program);
	glValidateProgram(program);


	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}







bool Shader::CompileShader()
