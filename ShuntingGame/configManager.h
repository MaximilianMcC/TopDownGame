#pragma once

#include <string>

class ConfigManager
{
private:
	static std::string configFilePath;

public:
	static void Init();

	// TODO: Use generics isntead of doing this
	static void SetString(std::string key, std::string value);
	static void SetInt(std::string key, int value);
	static void SetBoolean(std::string key, bool value);

	// TODO: Use generics isntead of doing this
	static std::string GetString(std::string key);
	static int GetInt(std::string key) {};
	static bool GetBoolean(std::string key) {};
};