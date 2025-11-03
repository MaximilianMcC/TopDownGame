#include "player.h"

#include "assetManager.h"
#include "utils.h"
#include "numericalVectors.h"

void Player::Move()
{
	// Get the direction input
	sf::Vector2f direction;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) direction.x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) direction.x++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) direction.y--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) direction.y++;

	// If we moved then normalise it
	if (direction.length() != 0.0f) direction = direction.normalized();

	// Apply the movement to the player
	sf::Vector2f newMovement = (direction * speed) * Utils::DeltaTime;
	body.move(newMovement);
}

void Player::Rotate()
{
	// Get the vector towards the mouse position
	sf::Vector2f direction = Utils::GetMousePosition() - body.getPosition();

	// Turn the vector into an angle (sfml try not to overcomplicate everthing challenge)
	sf::Angle angle = sf::radians(std::atan2(direction.y, direction.x));

	// Rotate the player accordingly
	body.setRotation(angle);
}

void Player::Start()
{
	// Create the actual body
	body = sf::RectangleShape(sf::Vector2f(100.0f, 100.0f));
	body.setTexture(AssetManager::LoadAndGetTexture("player", "D:/test.png"));

	// Set its origin to be in the centre
	body.setOrigin(body.getSize() / 2.0f);
}

void Player::Update()
{
	Move();
	Rotate();
}

void Player::Draw()
{
	Utils::GetWindow()->draw(body);
}