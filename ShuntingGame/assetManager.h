/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : assetManager
Description : load assets
Author : Maximilian Oscar Jack McCarthy
Mail : maximilian.mccarthy@mds.ac.nz
**************************************************************************/

#pragma once
#include <map>
#include <string>
#include <shlobj.h>
#include <iostream>
#include "utils.h"
#include <Windows.h>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetManager
{
private:
static std::map<std::string, sf::SoundBuffer> sounds;
static std::map<std::string, sf::Texture> textures;
static std::map<std::string, sf::Cursor> cursors;
static std::map<std::string, sf::Image> images;
static std::map<std::string, sf::Font> fonts;

public:
	static sf::Texture* LoadTexture(std::string key, std::string path);
	static sf::Texture* LoadTexture(std::string key, sf::Image& image);
	static sf::Texture* GetTexture(std::string key);
	
	static sf::Image* LoadImage(std::string key, std::string path);
	static sf::Image* GetImage(std::string key);

	static sf::Font* LoadDefaultFont(std::string key, std::string fontFileName);
	static sf::Font* GetFont(std::string key);

	static sf::SoundBuffer* LoadSound(std::string key, std::string path);
	static sf::SoundBuffer* GetSound(std::string key);

	static sf::Texture* LoadTextureFromRenderTexture(std::string key, sf::RenderTexture& renderTexture);
};