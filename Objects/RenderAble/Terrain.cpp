#include "Terrain.h"

CTerrain::CTerrain()
{
	m_Quad.Init();
	for (auto& texture : m_Textures)
	{
		texture = nullptr;
	}
}
