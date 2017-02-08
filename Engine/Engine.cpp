#include "Engine.h"

CEngine::CEngine(const std::string & window_name, const int & w, const int & h, bool full_screen)
	: m_DisplayManager(window_name, w, h, full_screen)
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

		m_DisplayManager.Update();
		m_InputManager.CheckReleasedKeys();
	}
}

int CEngine::ReadConfiguration(const std::string & file_name)
{
	std::ifstream file;
	file.open(file_name);
	if (!file.is_open())
	{
		std::cout << "[Error] Cant open configuration file." << std::endl;
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