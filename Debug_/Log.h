#pragma once
#include <string>
#include <list>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "SDL2/SDL.h"
class CLogger
{
public:
	static CLogger& Instance()
	{
		static CLogger logger;
		return logger;
	}
	void EnableLogs()
	{
		enabled = true;
		CreateLogFile();
	}
	void Error(const std::string& log)
	{
		MessageBox(SDL_MESSAGEBOX_ERROR, "Error", log.c_str());
		Log(log);
	}
	void Log(const std::string& log)
	{
		if (!enabled)
			return;

		m_Logs.push_back(log);
		std::ofstream file(m_FileName, std::ios_base::app);
		file << log << '\n';
		file.close();
	}
	void MessageBox(Uint32 flags, const std::string& title, const std::string& message)
	{
		SDL_ShowSimpleMessageBox(flags,
			title.c_str(),
			message.c_str(),
			NULL);
	}
	void SaveToFile() const
	{
		std::ofstream file(m_FileName, std::ios_base::app);
		for (const auto& log : m_Logs)
			file << log.c_str() << '\n';
		file.close();
	}
	~CLogger() 
	{
	}
private:
	CLogger()
	{
		
	}	

	void CreateLogFile()
	{
		auto now = std::chrono::system_clock::now();
		auto in_time_t = std::chrono::system_clock::to_time_t(now);

		std::stringstream ss;
		ss << in_time_t;
		m_FileName = "Logs/Logs" + ss.str() + ".txt";
		std::ofstream file(m_FileName);
		file.close();
	}

	std::string m_FileName;
	std::list<std::string> m_Logs;
	bool enabled = false;
};

#define Log(x) do {CLogger::Instance().Log(x);} while(0)
#define Error(x) do {CLogger::Instance().Error(x);} while(0)