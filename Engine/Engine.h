#pragma once
#include "../Display/DisplayManager.hpp"
#include "../Input/InputManager.h"
#include <fstream>
#include "../Scene/Scene.hpp"

class CEngine
{
public:
	CEngine(const std::string& window_name, const int& w, const int& h, bool full_screen);
	int  ReadConfiguration(const std::string& file_name);
	void GameLoop();
private:
	CDisplayManager m_DisplayManager;
	CInputManager	m_InputManager;
	std::unique_ptr<CScene> m_Scene;
};
