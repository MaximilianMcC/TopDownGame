#include "debugger.h"

#include <string>
#include "inputHandler.h"
#include "assetManager.h"
#include "utils.h"
#include "level.h"

bool Debugger::Enabled = false;
sf::Text* Debugger::text = nullptr;

void Debugger::Start()
{
	// Make the text stuff
	text = new sf::Text(*AssetManager::GetFont("consolas"), "", 10U);
	text->setFillColor(sf::Color::Black);
	text->setPosition(sf::Vector2f(-50.0f, -50.0f));
}

void Debugger::Update()
{
	// Check for if we want to open/close the debug menu
	if (InputHandler::KeyPressed(sf::Keyboard::Key::Grave)) Enabled = !Enabled;
	if (Enabled == false) return;

	// controls idk
	if (InputHandler::KeyPressed(sf::Keyboard::Key::V)) Utils::UseVsync(!Utils::VsyncOn());

	if (InputHandler::KeyPressed(sf::Keyboard::Key::S)) Level::GotoNextLevel();
	if (InputHandler::KeyPressed(sf::Keyboard::Key::R)) Level::Restart();

	float volumeIncrease = 20.0f * Utils::DeltaTime;
	if (InputHandler::KeyHeldDown(sf::Keyboard::Key::Equal)) Utils::AddToMasterVolume(volumeIncrease);
	if (InputHandler::KeyHeldDown(sf::Keyboard::Key::Hyphen)) Utils::AddToMasterVolume(-volumeIncrease);

	// Updaet the text
	// TODO: think of more debug things to add
	std::string vsyncStatus = "(" + std::string(Utils::VsyncOn() ? "on" : "off") + ")";
	std::string musicVolume = "(" + std::to_string(Utils::GetMasterVolume()) + "% (needs restart))";
	text->setString("Press S to skip level\nPress R to reload level\nPress v to toggle vsync " + vsyncStatus + "\nPress +/- to change vol\n" + musicVolume);
}

void Debugger::Draw()
{
	if (Enabled == false) return;

	Utils::GetWindow()->draw(*text);
}

// TODO: Use a destructor
void Debugger::CleanUp()
{
	delete text;
	text = nullptr;
}
