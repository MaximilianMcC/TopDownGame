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
}

void Debugger::Update()
{
	// Check for if we want to open/close the debug menu
	if (InputHandler::KeyPressed(sf::Keyboard::Key::Grave)) Enabled = !Enabled;
	if (Enabled == false) return;

	// controls idk
	if (InputHandler::KeyPressed(sf::Keyboard::Key::S)) Level::GotoNextLevel();
	if (InputHandler::KeyPressed(sf::Keyboard::Key::V)) Utils::UseVsync(!Utils::VsyncOn());

	// Updaet the text
	// TODO: think of more debug things to add
	std::string vsyncStatus = "(" + std::string(Utils::VsyncOn() ? "on" : "off") + ")";
	text->setString("Press S to skip level\nPress v to toggle vsync " + vsyncStatus);
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
