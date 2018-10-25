#include"ParseShader.h"
#include<fstream>
#include<string>
#include<sstream>
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
