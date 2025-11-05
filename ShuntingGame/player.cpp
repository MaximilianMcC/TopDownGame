#include "player.h"

#include "assetManager.h"
#include "utils.h"
#include "numericalVectors.h"
#include "projectile.h"

void Player::Move()
{
	// Get the direction input
	sf::Vector2f direction;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) direction.x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) direction.x++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) direction.y--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) direction.y++;

	// Check for if we even moved
	if (direction.length() == 0.0f) return;
	direction = direction.normalized();

	// Apply the movement to the player
	sf::Vector2f newMovement = (direction * speed) * Utils::DeltaTime;
	body->Move(newMovement);
}

void Player::Rotate()
{
	// Get the vector towards the mouse position
	sf::Vector2f direction = Utils::GetMousePosition() - body->GetPosition();

	// Turn the vector into an angle (sfml try not to overcomplicate everthing challenge)
	sf::Angle angle = Utils::AngleFromVector(direction);

	// Rotate the player accordingly
	body->SetRotation(angle);
}

void Player::Shoot()
{
	// Check for if we click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false) return;

	// Spawn in a bullet
	Projectile* bullet = new Projectile;
	bullet->Init(body->GetPosition(), body->GetRotation());
	SceneManager::GetScene()->AddGameObject(bullet);
}

void Player::Start()
{
	// Create the actual body
	body = new Sprite("./assets/box.png", 16, 0.8f);
}

void Player::Update()
{
	Move();
	Rotate();
	Shoot();

	// Make the camera follow the player
	SceneManager::GetScene()->Camera.setCenter(body->GetPosition());
}

void Player::Draw()
{
	body->Draw();
}

void Player::CleanUp()
{
	delete body;
	body = nullptr;
}