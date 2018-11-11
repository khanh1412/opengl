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
		Texture(unsigned char* Image, int Height, int Width, int BPP);
		~Texture();

		void Bind(unsigned int slot=0) const;
		void Unbind(unsigned int slot=0) const;

		inline int GetWidth() const { return m_Width;}
		inline int GetHeight() const { return m_Height;}
};
#endif
