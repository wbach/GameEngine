#pragma once
#include "../GameObject.h"
#include "../../Resources/SimpleModels/Quad.h"
#include "../../Resources/Textures/Texture.h"

struct TerrainTextures
{
	CTexture* m_BlendMap			= nullptr;
	CTexture* m_BackgorundTexture	= nullptr;
	CTexture* m_RedTexture			= nullptr;
	CTexture* m_GreenTexture		= nullptr;
	CTexture* m_BlueTexture			= nullptr;
	CTexture* m_DisplacementMap		= nullptr;
};

class CTerrain : public CGameObject
{
public:
	enum TexturesTypes
	{
		blendMap = 0,
		backgorundTexture,
		redTexture,
		greenTexture,
		blueTexture,
		displacementMap,
		count
	};

	CTerrain();
	void SetTexture(CTexture* texture, TexturesTypes type)
	{
		if (type == TexturesTypes::count)
			return;

		m_Textures[type] = texture;
	}
private:
	SSimpleQuad m_Quad;
	float m_DispFactor;

	CTexture* m_Textures[TexturesTypes::count];
};