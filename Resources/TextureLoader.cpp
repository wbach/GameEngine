#include "TextureLoader.h"

CTextureLoader::CTextureLoader(std::vector<std::unique_ptr<CTexture>>& textures_vector, COpenGLLoader & openGLLoader)
	: m_Textures(textures_vector)
	, m_OpenGLLoader(openGLLoader)
{
}

void CTextureLoader::ReadFile(const std::string & file, SImage& image, TextureFlip::Type flip_mode)
{
	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(file.c_str(), 0);
	if (formato == FIF_UNKNOWN)
	{
		Log("[Error] wrong image format or file does not exist." + file);
		return;
	}

	FIBITMAP* imagen2 = FreeImage_Load(formato, file.c_str());
	if (!imagen2)
	{
		Log("[Error] wrong image format or file does not exist." + file);
		return;
	}

	FIBITMAP* imagen = FreeImage_ConvertTo32Bits(imagen2);
	if (!imagen)
	{
		FreeImage_Unload(imagen2);
		Log("[Error] Cant convert to 32 bits : " + file);
		return;
	}

	if (flip_mode == TextureFlip::VERTICAL || flip_mode == TextureFlip::BOTH)
		FreeImage_FlipVertical(imagen);
	if (flip_mode == TextureFlip::HORIZONTAL || flip_mode == TextureFlip::BOTH)
		FreeImage_FlipHorizontal(imagen);

	int w = FreeImage_GetWidth(imagen);
	int h = FreeImage_GetHeight(imagen);

	image.m_Width = w;
	image.m_Height = h;

	char* pixeles = (char*)FreeImage_GetBits(imagen);

	image.m_Data = new GLubyte[4 * w*h];
	//bgr2rgb
	for (int j = 0; j<w*h; j++)
	{
		image.m_Data[j * 4 + 0] = pixeles[j * 4 + 2];
		image.m_Data[j * 4 + 1] = pixeles[j * 4 + 1];
		image.m_Data[j * 4 + 2] = pixeles[j * 4 + 0];
		image.m_Data[j * 4 + 3] = pixeles[j * 4 + 3];
	}
	FreeImage_Unload(imagen);
	FreeImage_Unload(imagen2);
}

CTexture* CTextureLoader::LoadTexture(const std::string & file, bool opengl_pass, TextureType::Type type, TextureFlip::Type flip_mode)
{
	unsigned int id = 0;
	for (auto& t : m_Textures)
	{
		if (t->GetFileName().compare(file) == 0)
			return t.get();
		id++;
	}
	SImage texture;
	ReadFile(file, texture, flip_mode);

	switch (type)
	{
	case TextureType::MATERIAL:
		m_Textures.push_back(std::make_unique<CMaterialTexture>(false, file, file, texture));
		break;
	}
	if(opengl_pass)
		m_OpenGLLoader.AddObjectToOpenGLLoadingPass(m_Textures.back().get());
	return m_Textures.back().get();
}

CTexture * CTextureLoader::LoadTextureImmediately(const std::string & file, TextureType::Type type, TextureFlip::Type flip_mode)
{
	auto texture = LoadTexture(file, false, type, flip_mode);
	texture->OpenGLLoadingPass();
	return texture;
}
