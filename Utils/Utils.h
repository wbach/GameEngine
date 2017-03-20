#pragma once
#include <algorithm>
#include <sstream>
#include "GLM/GLMUtils.h"
#include "OpenGL/OpenGLUtils.h"
#include "XML/XMLUtils.h"
#include <fstream>
#include "../Debug_/Log.h"

#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288   /* pi */
#endif

#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

namespace wb
{
	struct vec2i
	{
		int x;
		int y;
	};
	struct vec3i
	{
		int x;
		int y;
		int z;

		bool operator==(const vec3i& v) const
		{
			return x == v.x && y == v.y && z == v.z;
		}
		//To my model map find
		bool operator<(const vec3i& v) const {
			return x != v.x || y != v.y || z != v.z;
		};
	};
}

namespace Get
{
	static float Float(std::string line)
	{
		return std::stof(line);
	}
	static int Int(std::string line)
	{
		return stoi(line);
	}
	static glm::vec2 Vector2d(std::string line, char prefix = 'x')
	{
		float x = std::stof(line.substr(0, line.find_last_of(prefix)));
		float y = std::stof(line.substr(line.find_last_of(prefix) + 1));
		return glm::vec2(x, y);
	}
	static glm::vec3 Vector3d(std::string line, char prefix = 'x')
	{
		float z = std::stof(line.substr(line.find_last_of(prefix) + 1));
		float x = std::stof(line.substr(0, line.find_first_of(prefix)));
		float y = std::stof(line.substr(line.find_first_of(prefix)+1, line.find_last_of(prefix)));
		return glm::vec3(x, y, z);
	}
	static bool Boolean(std::string line)
	{
		return std::stof(line) > 0 ? true : false;
	}
}

namespace Utils
{
	template <typename T>
	T clamp(const T& n, const T& lower, const T& upper) {
		return std::max(lower, std::min(n, upper));
	}

	template<class type>
	float ToRadians(type a)
	{
		return static_cast<float>(a) * static_cast<float>(M_PI) / 180.0f;
	}

	template<class type>
	type ToDegrees(type a)
	{
		return a * 180.0f / static_cast<float>(M_PI);
	}

	template<class type>
	type KmToMs(type a)
	{
		return a * 0.277777778f;
	}
	static std::vector<std::string> SplitString(const std::string& s, char split_char)
	{
		std::vector<std::string> tokens;
		std::string token;

		for (const auto& c : s)
		{
			if (c == split_char)
			{
				tokens.push_back(token);
				token.clear();
				continue;
			}
			token += c;
		}
		if (!token.empty())
			tokens.push_back(token);

		return tokens;
	}

	static std::string ReadFile(const std::string& file_name)
	{
		std::ifstream t(file_name);
        if (!t.is_open())
        {
            std::cout << ("Cannot open file : " + file_name) << std::endl;
            return std::string();
        }
        std::string out = std::string((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
        t.close();
        return out;
	}
	static void GetFileAndPath(const std::string& full, std::string& filename, std::string& path)
	{
		auto file = full;
		std::replace(file.begin(), file.end(), '\\', '/');
		path = file.substr(0, file.find_last_of('/'));
		filename = file.substr(file.find_last_of('/') + 1);
	}
	static std::string ConvertToRelativePath(std::string path)
	{
		if (path.empty()) return path;

		std::replace(path.begin(), path.end(), '\\', '/');
		std::size_t found = path.find("Data/");
		if (found != std::string::npos)
		{
			path = path.substr(found);
		}
		return path;
	}

	inline bool CheckFile(const std::string& name) {
		//struct stat buffer;
		//return (stat(name.c_str(), &buffer) == 0);
		return true;
	}

	template <typename T> std::string ToStr(const T& t)
	{
		std::ostringstream os;
		os << t;
		return os.str();
	}
	static int NextP2(int a)
	{
		int rval = 1;
		while (rval<a) rval <<= 1;
		return rval;
	}
}
