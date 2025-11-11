#pragma once

#include <string>

class ConfigManager
{
private:
	static std::string configFilePath;

public:
	static void Init();

	// TODO: Use generics isntead of doing this
	static void Set(std::string key, std::string value);
	// static void Set(std::string key, int value) {};
	// static void Set(std::string key, bool value) {};

	// TODO: Use generics isntead of doing this
	static std::string GetString(std::string key);
	static int GetInt(std::string key) {};
	static bool GetBoolean(std::string key) {};
};