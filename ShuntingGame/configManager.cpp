#include "configManager.h"

#include <windows.h>
#include <shlobj.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include "utils.h"

std::string ConfigManager::configFilePath;

void ConfigManager::Init()
{
	// Get the path to appdata
	char appDataPath[MAX_PATH];
	SHGetFolderPathA(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, appDataPath);

	// Get the path to the config file
	configFilePath = std::string(appDataPath) + "\\PuzzleGame\\config.ini";
	std::filesystem::create_directories(std::string(appDataPath) + "\\PuzzleGame");
	std::cout << configFilePath << std::endl;

	// If the file doesn't already exist then create
	// and populate it with some default data
	if (std::filesystem::exists(configFilePath) == false)
	{
		SetString("level", "./assets/levels/level1.txt");
		SetBoolean("vsync", false);
		SetInt("windowX", (int)Utils::GetWindow()->getSize().x);
		SetInt("windowY", (int)Utils::GetWindow()->getSize().y);

		// TODO: Add volume
		// TODO: Add a float datatype (or just `* 100` or whatever)
		// Set("volume", 30);
	}
	else
	{
		// 'Apply' everything that has been saved
		Utils::GetWindow()->setSize(sf::Vector2u(
			(unsigned int)GetInt("windowX"),
			(unsigned int)GetInt("windowY")
		));
		Utils::GetWindow()->setVerticalSyncEnabled(GetBoolean("vsync"));
	}
}

//! overwrites file rn
void ConfigManager::SetString(std::string key, std::string value)
{
	// Get what our new line will be and save
	// watever was previously in the file
	bool updated = false;
	std::vector<std::string> fileLines;
	std::string newLine = key + ": " + value;

	// Open the file (if it exists)
	// TODO: Guard clause
	if (std::filesystem::exists(configFilePath))
	{
		// Read and 'modify' the file
		std::ifstream config(configFilePath);
		std::string line;
		while (std::getline(config, line))
		{
			// Find the key we want
			std::string currentKey = Utils::Split(line, ": ")[0];
			if (currentKey == key)
			{
				// Replace it with our new value
				line = newLine;
				updated = true;
			}

			// Save the line
			fileLines.push_back(line);
		}
		config.close();
	}

	// If our key didn't exist then add it
	if (updated == false) fileLines.push_back(newLine);
	
	// Write everything back/to the file
	std::ofstream updatedConfig(configFilePath);
	for (std::string& line : fileLines)
	{
		// Print the line
		updatedConfig << line << std::endl;
	}
	updatedConfig.close();
}

void ConfigManager::SetInt(std::string key, int value)
{
	SetString(key, std::to_string(value));
}

void ConfigManager::SetBoolean(std::string key, bool value)
{
	SetString(key, std::to_string(value));
}

std::string ConfigManager::GetString(std::string key)
{
	// Open the file
	std::ifstream config(configFilePath);
	if (!config)
	{
		// TOOD: Run init for them
		std::cerr << "issue loading config (make sure you ran init)";
		return "idk";
	}

	// Loop over every line until we find the one
	// that contains the key we are looking for
	std::string line;
	while (std::getline(config, line))
	{
		// Find the key we want
		std::string currentKey = Utils::Split(line, ": ")[0];
		if (currentKey == key)
		{
			// Give back the value as a string
			Utils::ReplaceAll(line, (key + ": "), "");
			return line;
		}
	}
	
	// Couldn't find it
	std::cerr << "No key of the name '" << key << "' found.\n";
	return "idk";
}

int ConfigManager::GetInt(std::string key)
{
	return std::stoi(GetString(key));
}

bool ConfigManager::GetBoolean(std::string key)
{
	// Don't do this because this is just weird as
	return GetInt(key);
}
