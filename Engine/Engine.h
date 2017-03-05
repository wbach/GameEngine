#pragma once
#include "../Display/DisplayManager.hpp"
#include "../Input/InputManager.h"
#include <fstream>
#include "../Scene/Scene.hpp"
#include "../Renderers/Entity/EntityRenderer.h"
#include "../Renderers/LodingScreenRenderer.h"
#include "Projection.h"
#include "../Resources/ResourceManager.h"
#include "../Renderers/SimpleRenderer.h"

class CEngine
{
public:
	CEngine(const std::string& window_name, const int& w, const int& h, bool full_screen);
	int  ReadConfiguration(const std::string& file_name);
	void Init();
	void GameLoop();
	void OpenGLLoadingPass(std::thread& loading_thread);
	void PreperaScene();
	void LoadScene();
	void SetIsLoading(bool is);
	bool GetIsLoading();

	CDisplayManager m_DisplayManager;
	CInputManager	m_InputManager;
	std::unique_ptr<CScene> m_Scene;
private:	
	std::unique_ptr<CLoadingScreenRenderer> m_LoadingScreenRenderer;
	std::vector<std::unique_ptr<CRenderer>> m_Renderers;

	SProjection m_Projection;
	//Global items, loading screen etc...
	CResourceManager m_ResorceManager;

	bool m_IsLoading;
	std::mutex m_LoadingMutex;
};
