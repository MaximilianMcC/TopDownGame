#include "projectile.h"

#include "assetManager.h"
#include "utils.h"

void Projectile::Start()
{
	body = sf::RectangleShape();
	body.setSize(sf::Vector2f(5.0f, 5.0f));
	body.setTexture(AssetManager::LoadTexture("bullet", "D:/test.png"));
}

void Projectile::Update()
{
	// Move the bullet
	sf::Vector2f direction = Utils::VectorFromAngle(body.getRotation());
	sf::Vector2f movement = (direction * speed) * Utils::DeltaTime;
	body.move(movement);
}

void Projectile::Draw()
{
	Utils::GetWindow()->draw(body);
}

void Projectile::Init(sf::Vector2f position, sf::Angle direction)
{
	body.setPosition(position);
	body.setRotation(direction);
}
