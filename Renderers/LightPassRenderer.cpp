#include "LightPassRenderer.h"

CLightPassRenderer::CLightPassRenderer(SProjection * projection)
	: m_Projection(projection)
{
}

void CLightPassRenderer::Init()
{
	m_Shader.Init();
	m_Shader.Start();
	m_Shader.LoadSkyColour(glm::vec3(0.0));
	m_Shader.LoadScreenSize(m_Projection->GetWindowSize());
	m_Shader.LoadViewDistance(m_Projection->GetViewDistance());
	m_Shader.Stop();

	m_Quad.Init();
}

void CLightPassRenderer::PrepareFrame(CScene * scene)
{	
}

void CLightPassRenderer::Render(CScene * scene)
{	
	m_Shader.Start();
	m_Shader.LoadSkyColour(glm::vec3(0.8) /** scene->m_DayNightCycle.GetDayNightBlendFactor()*/);
	m_Shader.LoadCameraPosition(scene->GetCamera()->GetPosition());
	m_Shader.LoadLight(scene->GetDirectionalLight(), 0);
	int lights = scene->GetLights().size() + 1;
	m_Shader.LoadLightNumber(lights);
	int i = 1;
	for (const auto& light : scene->GetLights())
	{
		m_Shader.LoadLight(light, i++);
	}
	m_Quad.Render();
	m_Shader.Stop();
}

void CLightPassRenderer::EndFrame(CScene * scene)
{
	
}
