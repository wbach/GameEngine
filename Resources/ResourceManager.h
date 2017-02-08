#pragma once
#include "Models/Model.h"
#include <vector>
#include <memory>

class CResourceManager
{
public:

private:
	std::vector<std::unique_ptr<CModel>>    m_Models;
	std::vector<std::unique_ptr<CTextInfo>>	m_Textures;
};