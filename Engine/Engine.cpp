#include "Engine.h"

CEngine::CEngine(const std::string & window_name, const int & w, const int & h, bool full_screen)
	: m_DisplayManager(window_name, w, h, full_screen)
	, m_Projection({w, h})
{
	m_DisplayManager.SetInput(m_InputManager.m_Input);
}

void CEngine::GameLoop()
{
	ApiMessages::Type m_ApiMessage = ApiMessages::NONE;

	while (m_ApiMessage != ApiMessages::QUIT)
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(.8f, .8f, .8f, 1.f);

		m_ApiMessage = m_DisplayManager.PeekMessage();

		if (m_InputManager.GetKey(KeyCodes::ESCAPE))
			m_ApiMessage = ApiMessages::QUIT;		

		if (m_Scene != nullptr)
		{
			switch (m_Scene->Update())
			{
			case 1: m_ApiMessage = ApiMessages::QUIT; break;
			}

			m_Renderer->PrepareFrame(m_Scene.get());
			m_Renderer->Render(m_Scene.get());
			m_Renderer->EndFrame(m_Scene.get());
					
		}
		m_DisplayManager.Update();
		m_InputManager.CheckReleasedKeys();
	}
}

void CEngine::OpenGLLoadingPass(std::thread& loading_thread)
{

	int x = 0;
	bool  load = true;
	m_DisplayManager.GetSync() = true;
	bool post_load = false;
	while (load)
	{
		m_DisplayManager.PeekMessage();

		load = GetIsLoading();

		auto obj = m_Scene->GetResourceManager().GetOpenGlLoader().GetObjectToOpenGLLoadingPass();
		if (obj != nullptr)
		{
			load = true;
			obj->OpenGLLoadingPass();
		}

		m_LoadingScreenRenderer->Render(nullptr);
		m_DisplayManager.Update();
	}
	loading_thread.join();
	load = true;
	while (load)
	{
		m_DisplayManager.PeekMessage();
		auto obj = m_Scene->GetResourceManager().GetOpenGlLoader().GetObjectToOpenGLPostLoadingPass();
		if (obj != nullptr)
		{
			load = true;
			obj->OpenGLPostLoadingPass();
		}
		else
		{
			load = false;
		}
		m_LoadingScreenRenderer->Render(nullptr);
		m_DisplayManager.Update();
	}
}

void CEngine::LoadScene()
{
	if (m_Scene == nullptr) return;
	auto start = std::chrono::high_resolution_clock::now();
	m_Scene->Initialize();
	auto end = std::chrono::high_resolution_clock::now();
	Log("Scene loading time: " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.f ) + "s.");
//	std::this_thread::sleep_for(std::chrono::seconds(10));
	SetIsLoading(false);
}

void CEngine::SetIsLoading(bool is)
{
	std::lock_guard<std::mutex> lock(m_LoadingMutex);
	m_IsLoading = is;
}

bool CEngine::GetIsLoading()
{
	std::lock_guard<std::mutex> lock(m_LoadingMutex);
	return m_IsLoading;
}

int CEngine::ReadConfiguration(const std::string & file_name)
{
	std::ifstream file;
	file.open(file_name);
	if (!file.is_open())
	{
		Log("[Error] Cant open configuration file.");
		return -1;
	}
	std::string line;

	while (std::getline(file, line))
	{
		std::string var = line.substr(0, line.find_last_of("="));
		std::string value = line.substr(line.find_last_of("=") + 1);

		/*	if (var.compare("Name") == 0)				m_WindowName = value;
		if (var.compare("Resolution") == 0)			m_WindowSize = Get::Vector2d(value);
		if (var.compare("FullScreen") == 0)			m_IsFullScreen = Get::Boolean(value);
		if (var.compare("RefreshRate") == 0)		m_RefreshRate = Get::Int(value);
		if (var.compare("Sound") == 0)				m_IsSound = Get::Boolean(value);
		if (var.compare("SoundVolume") == 0)		m_SoundVolume = Get::Float(value);
		if (var.compare("RenderingResolution") == 0)	m_RenderingResolutionModifier = Get::Float(value);
		if (var.compare("WaterQuality") == 0)		m_WaterQuality = Get::Float(value);
		if (var.compare("WaterReflectionResolution") == 0)	m_ReflectionSize = Get::Vector2d(value);
		if (var.compare("WaterRefractionResolution") == 0)	m_RefractionSize = Get::Vector2d(value);
		if (var.compare("TextureMaxResolution") == 0)	m_MaxTextureResolution = Get::Vector2d(value);
		if (var.compare("Shadows") == 0)			m_IsShadows = Get::Boolean(value);
		if (var.compare("ShadowsDistance") == 0)	m_ShadowsDistance = Get::Float(value);
		if (var.compare("ShadowMapSize") == 0)		m_ShadowMapSize = Get::Float(value);
		if (var.compare("ViewDistance") == 0)		m_ViewDistance = Get::Float(value);
		if (var.compare("GrassViewDistance") == 0)	m_GrassViewDistance = Get::Float(value);
		if (var.compare("SimpleRender") == 0)		m_UsingSimpleRender = Get::Boolean(value);*/

	}
	file.close();
	return 0;
}

void CEngine::Init()
{
	glEnable(GL_DEPTH_TEST);

	//if (m_Renderer == nullptr)
	//{
	//	Error("Main Renderer not set!");
	//		exit(-1);
	//}
	m_Renderer = std::make_unique<FullRenderer>(&m_Projection);

	m_Renderer->Init();
	
	auto circleTexture	= m_ResorceManager.GetTextureLaoder().LoadTextureImmediately("../Data/GUI/circle2.png");
	auto bgtexture		= m_ResorceManager.GetTextureLaoder().LoadTextureImmediately("../Data/GUI/black-knight-dark-souls.png", TextureType::MATERIAL, TextureFlip::VERTICAL);
	m_LoadingScreenRenderer = std::make_unique<CLoadingScreenRenderer>(bgtexture, circleTexture);
	m_LoadingScreenRenderer->Init();
}
void CEngine::PreperaScene()
{
	m_IsLoading = true;
	std::thread loading_thread(&CEngine::LoadScene, this);
	OpenGLLoadingPass(loading_thread);
}
