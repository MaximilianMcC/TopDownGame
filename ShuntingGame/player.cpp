#include "player.h"

#include "assetManager.h"
#include "utils.h"

void Player::Start()
{
	body = sf::RectangleShape(sf::Vector2f(100.0f, 100.0f));
	body.setTexture(AssetManager::LoadAndGetTexture("player", "D:/test.png"));
}

void Player::Update()
{
	// Get the direction input
	sf::Vector2f direction;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) direction.x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) direction.x++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) direction.y--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) direction.y++;

	// If we moved then normalise it
	if (direction.length() != 0.0f) direction.normalized();

	// Apply the movement to the player
	sf::Vector2f newMovement = (direction * speed) * Utils::DeltaTime;
	body.move(newMovement);
}

void Player::Draw()
{
	Utils::GetWindow()->draw(body);
}