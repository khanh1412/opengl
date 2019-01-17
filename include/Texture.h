#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include"Renderer.h"
class Texture
{
	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;
	public:
		Texture(const std::string& path);
		//bind a buffer image. 1 channel
		Texture(unsigned char* Image, int Height, int Width, int BPP);
		~Texture();

		void Bind(unsigned int slot=0) const;
		void Unbind(unsigned int slot=0) const;

		inline int getWidth() const { return m_Width;}
		inline int getHeight() const { return m_Height;}
		inline int getBPP() const { return m_BPP;}
		inline unsigned int getID() const {return m_RendererID;}
};
#include"vendor/stb_image.h"
Texture::Texture(const std::string& path)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);	
	
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);//GL_RGBA IS SUPPLIED DATA, GL_UNSIGNED_BYTE IS TYPE OF DATA
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}
Texture::Texture(unsigned char* Image, int Height, int Width, int BPP)
	        : m_RendererID(0), m_LocalBuffer(Image),
		        m_Width(Width), m_Height(Height), m_BPP(BPP)
{
	        glGenTextures(1, &m_RendererID);
		        glBindTexture(GL_TEXTURE_2D, m_RendererID);


			        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
						        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

							        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_Width, m_Height, 0, GL_RED, GL_UNSIGNED_BYTE, m_LocalBuffer);//GL_RGBA IS SUPPLIED DATA, GL_UNSIGNED_BYTE IS TYPE OF DATA
								        glBindTexture(GL_TEXTURE_2D, 0);
}
Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}
void Texture::Unbind(unsigned int slot) const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
#endif
